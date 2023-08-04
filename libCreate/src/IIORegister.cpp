#include "IIORegister.h"
#include <bitset>

IIO_Registers::IIO_Registers()
{
}

IIO_Registers::~IIO_Registers()
{
    delete pCtx;
    delete pDev;
}

uint64_t curr_mill()
{
    struct timeval tmp_tv; // 当前时间的毫秒数时间戳
    gettimeofday(&tmp_tv, nullptr);
    uint64_t tmp_ms = tmp_tv.tv_usec / 1e3 + tmp_tv.tv_sec * 1e3;
    // LOGD("-------curr_mill-------%d,%d,%llu\n", tmp_tv.tv_usec, tmp_tv.tv_sec, tmp_ms);
    return tmp_ms;
}

uint64_t curr_micro()
{
    struct timeval tmp_tv; // 当前时间的微秒数时间戳
    gettimeofday(&tmp_tv, nullptr);
    uint64_t tmp_ms = tmp_tv.tv_usec + tmp_tv.tv_sec * 1e6;
    // LOGD("-------curr_micro-------%d,%d,%llu\n", tmp_tv.tv_usec, tmp_tv.tv_sec, tmp_ms);
    return tmp_ms;
}

/**
 * @brief 初始化iio
 *
 * @param ip 格式 ip:192.168.1.13
 * @return int 1成功 0失败
 */
int IIO_Registers::initIIO(std::string ip)
{
    pCtx = new Context(ip);

    if (pCtx->context() == nullptr)
    {
        return 0;
    }
    pDev = new Device(pCtx);
    if (pDev == nullptr)
    {
        delete pCtx;
        return 0;
    }
    this->setLedAlarm(false);
    this->setBuzzerAlarm(false);
    this->setMotorAlarm(false);
    this->setBuzzerLevel(0);
    this->setLightLevel(0);
    return 1;
}

/**
 * @brief setAlarmBit 设置bit位
 * @param type
 * @param a 左移多少位
 */
void IIO_Registers::setAlarmBit(uint32_t command)
{
    uint32_t old_command;
    pDev->alarm(old_command, 1);
    // std::cout << "setAlarmBit:  " << std::bitset<32>(old_command) << std::endl;

    old_command |= command;
    pDev->set_alarm(old_command, 1);
}

/**
 * @brief resetBit 取消bit位
 * @param type
 * @param a 左移多少位
 */
void IIO_Registers::resetAlarmBit(uint32_t command)
{
    uint32_t old_command;
    pDev->alarm(old_command, 1);
    // std::cout << "resetBit:" << std::bitset<32>(old_command) << std::endl;

    old_command &= ~(command);
    pDev->set_alarm(old_command, 1);
}

/**
 * @brief getAlarmBit 获取alarm bit (iio:device0:altvoltage1:alarm)
 * @param a 多少位
 */
int IIO_Registers::getAlarmBit(uint8_t a)
{
    uint32_t command;
    uint32_t operationBit = 0;

    operationBit |= 1 << a;
    pDev->alarm(command, 1);

    return (operationBit & command) >> a;
}

// 得到告警哪一位的值
uint32_t IIO_Registers::getAlarmBit(int type)
{
    uint32_t bit = 0;
    bit = 1 << type;
    return bit;
}

void IIO_Registers::writeAlarmBit(uint8_t wbit, uint32_t value)
{
    uint32_t bit = 0;
    bit |= 15 << wbit;
    resetAlarmBit(bit);
    setAlarmBit(value << wbit);
}

/**
 * @brief 设置音量等级
 *
 * @param level 等级0~15
 * @return int
 */
int IIO_Registers::setBuzzerLevel(int level)
{
    if (level < 0 || level > 15)
    {
        printf("Input not in range (0, 15)\n");
        return 0;
    }
    writeAlarmBit(BUZZER_LEVEL, level);
    // uint32_t bit = 0;
    // bit |= 15 << BUZZER_LEVEL;
    // resetAlarmBit(bit);
    // setAlarmBit(level << BUZZER_LEVEL);
    return 1;
}

/**
 * @brief 设置屏幕亮度
 *
 * @param level 等级0~15
 * @return int
 */
int IIO_Registers::setLightLevel(int level)
{
    if (level < 0 || level > 15)
    {
        printf("Input not in range (0, 15)\n");
        return 0;
    }
    setAlarmBit(1 << 13); // 只有将13位置1才能调光
    writeAlarmBit(SCREEN_LEVEL, level);
    // uint32_t bit = 0;
    // bit |= 15 << BUZZER_LEVEL;
    // resetAlarmBit(bit);
    // setAlarmBit(level << BUZZER_LEVEL);
    return 1;
}

/**
 * @brief 设置IIO管脚 (iio:device0:altvoltage1:alarm)
 *
 * @param bit 哪一位
 * @param value 置0或者置1
 * @return int
 */
int IIO_Registers::setControlIIO(uint8_t bit, uint8_t value)
{
    uint32_t w_bit = 0;
    w_bit |= 1 << bit;

    if (value == 1)
        setAlarmBit(w_bit);
    else if (value == 0)
        resetAlarmBit(w_bit);
}

/**
 * @brief 获取bit位 (iio:device0:altvoltage1:alarm)
 *
 * @param bit
 * @return int
 */
int IIO_Registers::getControlIIO(uint8_t bit)
{
    return getAlarmBit(bit);
}

/**
 * @brief 控制开关板 (iio:device0:altvoltage1:ant_switch)
 *
 * @param value 传入16进制数
 * @return true
 * @return false
 */
bool IIO_Registers::setAntSwitch(uint32_t value)
{
    return pDev->set_switch(value) == 0;
}

/**
 * @brief (iio:device0:altvoltage1:alarm)
 *
 * @param _switch true开  false关
 * @param duration 时长 单位s
 * @param mode 模式 参考emun
 * @return int
 */
void IIO_Registers::setAlarmParam(int type, uint64_t duration, uint32_t mode, uint64_t interval_time)
{
    if (type == BUZZER)
    {
        buzzerThread.duration = duration;
        buzzerThread.mode = mode;
        buzzerThread.startTime = curr_mill();
    }
    else if (type == LED1)
    {
        ledThread.duration = duration;
        ledThread.mode = mode;
        ledThread.startTime = curr_mill();
    }
    else if (type == MOTOR)
    {
        motorThread.duration = duration;
        motorThread.mode = mode;
        motorThread.interval_time = interval_time;
        motorThread.startTime = curr_mill();
    }
}

/**
 * @brief
 *
 * @param _switch true开  false关
 * @param seconds 时长 单位s
 * @param mode 模式 参考BuzzerMode
 * @return int
 */
int IIO_Registers::setBuzzerAlarm(bool _switch, uint64_t duration, uint32_t mode)
{
    if (_switch == true)
    {
        if (buzzerThread.running == false)
        {
            buzzerThread.thread_ = std::thread(&IIO_Registers::_buzzer_thread, this, duration, mode);
            buzzerThread.running = true;
            buzzerThread.thread_.detach();
        }
        else
        {
            setAlarmParam(BUZZER, duration, mode);
        }
    }
    else if (_switch == false)
    {
        buzzerThread.running = false;
        uint32_t bit = getAlarmBit(BUZZER);
        if (getAlarmBit(BUZZER) == 1)
            resetAlarmBit(bit);
    }
}

/**
 * @brief
 *
 * @param _switch true开  false关
 * @param seconds 时长 单位 秒 s
 * @param mode 模式 参考BuzzerMode
 * @return int
 */
int IIO_Registers::setLedAlarm(bool _switch, uint64_t duration, uint32_t mode)
{
    if (_switch == true)
    {
        if (ledThread.running == false)
        {
            ledThread.thread_ = std::thread(&IIO_Registers::_led_thread, this, duration, mode);
            ledThread.running = true;
            ledThread.thread_.detach();
        }
        else
        {
            setAlarmParam(LED1, duration, mode);
        }
    }
    else if (_switch == false)
    {
        ledThread.running = false;
        uint32_t bit = getAlarmBit(LED1);
        if (getAlarmBit(LED1) == 1)
            resetAlarmBit(bit);
    }
}

/**
 * @brief
 *
 * @param _switch       开关 true开
 * @param duration      告警时长
 * @param mode          告警模式 参考MotorMode
 * @param interval_time 告警间隔事件 单位ms 处于M_INTERVAL模式生效
 * @return int
 */
int IIO_Registers::setMotorAlarm(bool _switch, uint64_t duration, uint32_t mode, uint64_t interval_time)
{
    if (_switch == true)
    {
        if (motorThread.running == false)
        {
            motorThread.thread_ = std::thread(&IIO_Registers::_motor_thread, this, duration, mode, interval_time);
            motorThread.running = true;
            motorThread.thread_.detach();
        }
        else
        {
            setAlarmParam(MOTOR, duration, mode, interval_time);
        }
    }
    else if (_switch == false)
    {
        motorThread.running = false;
        uint32_t bit = getAlarmBit(MOTOR);
        if (getAlarmBit(MOTOR) == 1)
            resetAlarmBit(bit);
    }
}

std::thread::id IIO_Registers::_led_thread_id()
{
    std::thread::id id = ledThread.thread_.get_id();
    // std::cout << this->ledThread.thread_.get_id() << std::endl;
    // std::cout << id << std::endl;
    return id;
}

void IIO_Registers::_buzzer_thread(uint64_t duration, uint32_t mode)
{
    buzzerThread.startTime = curr_mill();
    printf("now: %ld\n", buzzerThread.startTime);

    buzzerThread.mode = mode;
    buzzerThread.duration = duration;

    uint32_t bit = getAlarmBit(BUZZER);
    while (buzzerThread.running == true)
    {
        setAlarmBit(bit);
        usleep(buzzerThread.mode * 1000 / 2);
        resetAlarmBit(bit);
        usleep(buzzerThread.mode * 1000 / 2);

        if (curr_mill() - buzzerThread.startTime > buzzerThread.duration * 1000)
            buzzerThread.running = false;
    }
}

void IIO_Registers::_led_thread(uint64_t duration, uint32_t mode)
{
    ledThread.startTime = curr_mill();
    printf("now: %ld\n", ledThread.startTime);

    ledThread.mode = mode;
    ledThread.duration = duration;

    uint32_t bit = getAlarmBit(LED1);
    while (ledThread.running == true)
    {
        setAlarmBit(bit);
        usleep(ledThread.mode * 1000 / 2);
        resetAlarmBit(bit);
        usleep(ledThread.mode * 1000 / 2);

        if (curr_mill() - ledThread.startTime > ledThread.duration * 1000)
            ledThread.running = false;
    }
}

/**
 * @brief 马达告警线程函数
 *
 * @param duration      时长
 * @param mode          模式 见MotorMode
 * @param interval_time 间隔时间
 */
void IIO_Registers::_motor_thread(uint64_t duration, uint32_t mode, uint64_t interval_time)
{
    motorThread.startTime = curr_mill();
    printf("now: %ld\n", motorThread.startTime);

    motorThread.mode = mode;
    motorThread.duration = duration;
    motorThread.interval_time = interval_time;

    uint32_t bit = getAlarmBit(MOTOR);
    while (motorThread.running == true)
    {
        if (motorThread.mode == M_SUSTAIN)
            setAlarmBit(bit);
        else if (motorThread.mode = M_INTERVAL)
        {
            setAlarmBit(bit);
            usleep(motorThread.interval_time * 1000 / 2);
            resetAlarmBit(bit);
            usleep(motorThread.interval_time * 1000 / 2);
        }

        if (curr_mill() - motorThread.startTime > motorThread.duration * 1000)
        {
            resetAlarmBit(bit);
            motorThread.running = false;
        }
    }
}

/**
 * @brief 启动按键识别
 *
 */
void IIO_Registers::initKeys(CallbackFunction callback)
{
    if (keysThread.running == true)
    {
        printf("keys thread running\n");
        return;
    }
    keysThread.thread_ = std::thread(&IIO_Registers::_keyBroadIIO_thread, this, callback);
    keysThread.running = true;
    keysThread.thread_.detach();
}

/**
 * @brief 停止按键识别
 *
 */
void IIO_Registers::killKeys()
{
    keysThread.running = false;
}

KeyBroad IIO_Registers::dealKeysTime(uint8_t key, uint64_t releaseTime, uint64_t pressTime)
{
    KeyBroad keyBroad;
    memset(&keyBroad, 0, sizeof(KeyBroad));
    keyBroad.key = key;

    int time = releaseTime - pressTime;
    // printf("keyTime:%d\n", time);

    if (key != 0)
    {
        if (time >= 0)
        {
            if (time < 200)
                keyBroad.value = 1;
            else
                keyBroad.value = 0;
        }
        else
        {
            if (std::abs(time) > 500)
                keyBroad.value = 2;
            else
                keyBroad.value = 0;
        }
    }

    return keyBroad;
}

int IIO_Registers::readKeys(KeyBroad &keys)
{
    uint32_t ba = 0;
    pDev->get_keys(ba, 1);
    if ((ba & 0x1f) == 0x1f)
    {
        key_timer.release_tm = curr_mill();
        // std::cout << "未按下" << std::endl;
    }
    if ((ba & 1) == 0)
    {
        keys.key = KEYS::UP;
        key_timer.press_tm = curr_mill();
        // std::cout << "上" << std::endl;
    }
    if ((ba & 2) == 0)
    {
        keys.key = KEYS::DOWN;
        key_timer.press_tm = curr_mill();
        // std::cout << "下" << std::endl;
    }
    if ((ba & 4) == 0)
    {
        keys.key = KEYS::LEFT;
        key_timer.press_tm = curr_mill();
        // std::cout << "左" << std::endl;
    }
    if ((ba & 8) == 0)
    {
        keys.key = KEYS::RIGHT;
        key_timer.press_tm = curr_mill();
        // std::cout << "右" << std::endl;
    }
    if ((ba & 0x10) == 0)
    {
        keys.key = KEYS::OK;
        key_timer.press_tm = curr_mill();
        // std::cout << "确认" << std::endl;
    }

    KeyBroad key_test = dealKeysTime(keys.key, key_timer.release_tm, key_timer.press_tm);

    if (key_test.value != 0)
    {
        keys = key_test;
        return 1;
    }

    return 0;
}

void IIO_Registers::_keyBroadIIO_thread(CallbackFunction callback)
{
    KeyBroad keys;
    key_timer.old_key = 255;
    key_timer.press_tm = curr_mill();
    key_timer.release_tm = curr_mill();

    while (keysThread.running == true)
    {
        int tt = readKeys(keys);
        if (tt == 1)
        {
            // if (keys.value == 2)
            // {
            //     if (keys.key == key_timer.old_key)
            //     {
            //         memset(&keys, 0, sizeof(KeyBroad));
            //         continue;
            //     }
            //     key_timer.old_key = keys.key;
            // }
            callback(keys);

            // printf("key:%d value:%d\n", keys.key, keys.value);

            memset(&keys, 0, sizeof(KeyBroad));
        }
        usleep(30 * 1000);
    }
}
void IIO_Registers::_keyBroadEvent_thread()
{
    KeyBroad keys;

    int keys_fd;
    struct input_event t;
    const char *key_file = "/dev/input/event0";
    keys_fd = open(key_file, O_RDONLY);
    if (keys_fd <= 0)
    {
        printf("open %s error\n", key_file);
        keysThread.running = false;
        // return -1;
    }
    while (keysThread.running == true)
    {
        read(keys_fd, &t, sizeof(struct input_event));
        if (t.type == 1)
            printf("key code:%i value:%i type:%i, time:%i\n", t.code, t.value, t.type, t.time);
        usleep(30 * 1000);
    }
}

void IIO_Registers::performCallback(CallbackFunction callback)
{
    KeyBroad key;
    key.key = 26;
    key.value = 1;

    callback(key);
}