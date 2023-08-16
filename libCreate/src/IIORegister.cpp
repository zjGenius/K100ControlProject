#include "IIORegister.h"
#include <bitset>

IIO_Registers *IIO_Registers::m_IIORegisters = nullptr;
std::mutex IIO_Registers::m_mutex;

IIO_Registers::IIO_Registers()
{
}

IIO_Registers::~IIO_Registers()
{
    delete pCtx;
    delete pDev;
}

/**
 * @brief 初始化操作
 *
 * @param ip
 * @param mode
 * @return IIO_Registers*
 */
IIO_Registers *IIO_Registers::initIIORegister(std::string ip, uint8_t mode)
{
    if (m_IIORegisters == nullptr)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        if (m_IIORegisters == nullptr)
        {
            auto temp = new (std::nothrow) IIO_Registers();
            m_IIORegisters = temp;
            printf("IIO Registers init success\n");
        }
        else
        {
            printf("IIO Registers exist\n");
        }
    }
    else
    {
        printf("IIO Registers exist\n");
    }
    // std::string dev_ip = "ip:192.168.100.233";
    if (m_IIORegisters->initIIO(ip) == 0)
    {
        printf("IIO init failed.\n");
        m_IIORegisters = nullptr;
    }
    return m_IIORegisters;
}

/**
 * @brief 销毁对象
 *
 * @return IIO_Registers*
 */
IIO_Registers *IIO_Registers::deleteIIORegister()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    if (m_IIORegisters)
    {
        delete m_IIORegisters;
        m_IIORegisters = nullptr;
    }
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
int IIO_Registers::getIIOAlarmBit(uint8_t a)
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
    return 1;
}

/**
 * @brief 设置屏幕亮度
 *
 * @param level 等级0~15 0屏幕熄灭
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
    return getIIOAlarmBit(bit);
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
        buzzerThread.interval_time = interval_time;
        buzzerThread.startTime = curr_mill();
    }
    else if (type == LED1)
    {
        ledThread.duration = duration;
        ledThread.interval_time = interval_time;
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
 * @param interval_time 告警间隔时间(响不响间隔) 单位ms
 * @return int
 */
int IIO_Registers::setBuzzerAlarm(bool _switch, uint64_t duration, uint64_t interval_time)
{
    if (_switch == true)
    {
        if (buzzerThread.running == false)
        {
            buzzerThread.thread_ = std::thread(&IIO_Registers::_buzzer_thread, this, duration, interval_time);
            buzzerThread.running = true;
            buzzerThread.thread_.detach();
        }
        else
        {
            setAlarmParam(BUZZER, duration, 0, interval_time);
        }
    }
    else if (_switch == false)
    {
        buzzerThread.running = false;
        if (getIIOAlarmBit(BUZZER) == 1)
            resetAlarmBit(getAlarmBit(BUZZER));
    }
}

/**
 * @brief
 *
 * @param _switch true开  false关
 * @param seconds 时长 单位 秒 s
 * @param interval_time 告警间隔时间(亮灭间隔) 单位ms
 * @return int
 */
int IIO_Registers::setLedAlarm(bool _switch, uint64_t duration, uint64_t interval_time)
{
    if (_switch == true)
    {
        if (ledThread.running == false)
        {
            ledThread.thread_ = std::thread(&IIO_Registers::_led_thread, this, duration, interval_time);
            ledThread.running = true;
            ledThread.thread_.detach();
        }
        else
        {
            setAlarmParam(LED1, duration, 0, interval_time);
        }
    }
    else if (_switch == false)
    {
        ledThread.running = false;
        if (getIIOAlarmBit(LED1) == 1)
            resetAlarmBit(getAlarmBit(LED1));
    }
}

/**
 * @brief
 *
 * @param _switch       开关 true开
 * @param duration      告警时长
 * @param mode          告警模式 参考MotorMode
 * @param interval_time 告警间隔时间 单位ms 处于M_INTERVAL模式生效
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
        if (getIIOAlarmBit(MOTOR) == 1)
            resetAlarmBit(getAlarmBit(MOTOR));
    }
}

void IIO_Registers::_buzzer_thread(uint64_t duration, uint64_t interval_time)
{
    buzzerThread.startTime = curr_mill();
    // printf("now: %ld\n", buzzerThread.startTime);

    buzzerThread.interval_time = interval_time;
    buzzerThread.duration = duration;

    uint32_t bit = getAlarmBit(BUZZER);
    while (buzzerThread.running == true)
    {
        setAlarmBit(bit);
        usleep(buzzerThread.interval_time * 1000 / 2);
        resetAlarmBit(bit);
        usleep(buzzerThread.interval_time * 1000 / 2);

        if (curr_mill() - buzzerThread.startTime > buzzerThread.duration * 1000)
            buzzerThread.running = false;
    }
}

void IIO_Registers::_led_thread(uint64_t duration, uint64_t interval_time)
{
    ledThread.startTime = curr_mill();
    // printf("now: %ld\n", ledThread.startTime);

    ledThread.interval_time = interval_time;
    ledThread.duration = duration;

    uint32_t bit = getAlarmBit(LED1);
    while (ledThread.running == true)
    {
        setAlarmBit(bit);
        usleep(ledThread.interval_time * 1000 / 2);
        resetAlarmBit(bit);
        usleep(ledThread.interval_time * 1000 / 2);

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
    // printf("now: %ld\n", motorThread.startTime);

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

/**
 * @brief 识别按键长短按操作
 *
 * @param key
 * @param releaseTime
 * @param pressTime
 * @return KeyBroad
 */
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

/**
 * @brief 通过iio形式获取按键
 *
 * @param callback
 */
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
/**
 * @brief 通过设备获取按键
 *
 */
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
/**
 * @brief 初始化开关板逻辑
 *
 * @param mode
 */
void IIO_Registers::initAntswith(uint8_t mode)
{
    if (mode == ProductType::POCKET)
    {
        m_antSwitch.first = sizeof(pocketSwitch) / sizeof(Antswith);
        m_antSwitch.second = pocketSwitch;
    }
    else if (mode == ProductType::SHIELD)
    {
        m_antSwitch.first = sizeof(shieldSwitch) / sizeof(Antswith);
        m_antSwitch.second = shieldSwitch;
    }
    else
    {
        printf("Please enter the correct parameters\n");
    }
}
/**
 * @brief 设置开关板逻辑
 *
 * @param freq
 * @return int 0失败 1成功
 */
int IIO_Registers::setAntswith(int freq)
{
    for (int i = 0; i < m_antSwitch.first; i++)
    {
        if ((m_antSwitch.second + i)->freq[0] <= freq && freq <= (m_antSwitch.second + i)->freq[1])
        {
            uint param = ((m_antSwitch.second + i)->AntSwitchCode & 0xff) << 0;
            return pDev->set_switch(param, 1);
        }
    }
    return 0;
}

/*
    #天线切换逻辑
    [AntSwitch]
    #分段数
    antSwNum=6
    #频段从低到高排列
    [antSw0]
    freq=423,443
    AntSwitchCode=21
    [antSw1]
    freq=840,930
    AntSwitchCode=17
    [antSw2]
    freq=1420,1470
    AntSwitchCode=20
    [antSw3]
    freq=2400,2500
    AntSwitchCode=2
    [antSw4]
    freq=5200,5900
    AntSwitchCode=3
    [antSw5]
    freq=300,6000
    AntSwitchCode=5
*/

void IIO_Registers::performCallback(CallbackFunction callback)
{
    KeyBroad key;
    key.key = 26;
    key.value = 1;

    callback(key);
}

/*
    #天线切换逻辑
    [AntSwitch]
    #分段数
    antSwNum=6
    #频段从低到高排列
    [antSw0]
    freq=423,443
    AntSwitchCode=21
    [antSw1]
    freq=840,930
    AntSwitchCode=17
    [antSw2]
    freq=1420,1470
    AntSwitchCode=20
    [antSw3]
    freq=2400,2500
    AntSwitchCode=2
    [antSw4]
    freq=5200,5900
    AntSwitchCode=3
    [antSw5]
    freq=300,6000
    AntSwitchCode=5
*/
