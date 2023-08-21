/**
 * @file IIORegister.h
 * @author zhangjun (zhangjun.sole@qq.com)
 * @brief K100平台外设控制接口
 * @version 0.1
 * @date 2023-08-02
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef _IIO_REGISTER_H_
#define _IIO_REGISTER_H_

#include <string>
#include <thread>
#include <unistd.h>
#include <sys/time.h>
#include <atomic>
#include <linux/input.h>
#include <fcntl.h>
#include <mutex>

#include "SDR/context.h"
#include "SDR/device.h"
// #include "paramRead.h"

struct AlarmThread
{
    std::atomic_bool running; // 线程是否运行
    std::thread thread_;      // 线程
    uint64_t duration;        // 告警时长
    int mode;                 // 告警模式
    uint64_t startTime;       // 告警启动事件
    uint64_t interval_time;   // 告警间隔时间
};
// 按键识别
struct KeyBroad
{
    uint8_t key;   // 哪个键值 参考KEYS
    uint8_t value; // 状态 1短 2长
};
// 按键识别时间
struct KeyBroad_TM
{
    uint8_t old_key; //
    uint64_t press_tm = 0;
    uint64_t release_tm = 0;
};

/**
 * @brief 开关板通道
 *
 */
struct Antswith
{
    float freq[2];
    int AntSwitchCode;
};

enum MotorMode // 马达告警模式
{
    M_SUSTAIN, // 持续震
    M_INTERVAL // 间歇震
};

enum AlarmMode // 告警模式
{
    M_SHORT = 1, // 短
    M_MODERATE,  // 中
    M_LONG,      // 长
};

enum ALARM
{
    BUZZER,           // 蜂鸣器
    LED1,             // led1
    LED2,             // led2
    MOTOR = 3,        // 马达
    SCREEN = 8,       // 屏幕
    SCREEN_LEVEL = 9, // 屏幕亮度调节
    BUZZER_LEVEL = 14 // 蜂鸣器音量调节
};

enum KEYS
{
    UP = 1, // 上
    DOWN,   // 下
    LEFT,   // 左
    RIGHT,  // 右
    OK      // 确认
};

enum ProductType // 产品种类
{
    POCKET, // 口袋式
    SHIELD  // 盾
};

typedef void (*CallbackFunction)(KeyBroad &);
class IIO_Registers
{
private:
    static IIO_Registers *m_IIORegisters;
    static std::mutex m_mutex;

    Context *pCtx = nullptr;
    Device *pDev = nullptr;

    KeyBroad_TM key_timer;

    AlarmThread buzzerThread; // 蜂鸣器
    AlarmThread motorThread;  // 马达
    AlarmThread ledThread;    // led
    AlarmThread keysThread;   // 按键

    std::pair<int, Antswith *> m_antSwitch; // 开关板配置

    Antswith pocketSwitch[6]{{{423.0f, 433.0f}, 21},
                             {{840.0f, 930.0f}, 17},
                             {{1420.0f, 1470.0f}, 20},
                             {{2400.0f, 2500.0f}, 2},
                             {{5200.0f, 5900.0f}, 3},
                             {{300.0f, 6000.0f}, 5}}; // 口袋式开关板逻辑

    Antswith shieldSwitch[5]{{{423.0f, 433.0f}, 21},
                             {{840.0f, 930.0f}, 17},
                             {{1420.0f, 1470.0f}, 20},
                             {{2400.0f, 2500.0f}, 2},
                             {{5200.0f, 5900.0f}, 3}}; // 盾开关板逻辑

private:
    IIO_Registers();
    // IIO_Registers(std::string ip, uint8_t mode);
    ~IIO_Registers();
    IIO_Registers(IIO_Registers &iio);
    IIO_Registers &operator=(const IIO_Registers &iio);

    int initIIO(std::string ip);
    // 线程函数
    void _buzzer_thread(uint64_t seconds, uint64_t interval_time);
    void _led_thread(uint64_t seconds, uint64_t interval_time);
    void _motor_thread(uint64_t seconds, uint32_t mode, uint64_t interval_time = 0);
    void _keyBroadIIO_thread(CallbackFunction callback);
    void _keyBroadEvent_thread();

    void setAlarmBit(uint32_t command);
    void resetAlarmBit(uint32_t command);
    void writeAlarmBit(uint8_t bit, uint32_t value);
    int getIIOAlarmBit(uint8_t a);

    uint32_t getAlarmBit(int type);
    void setAlarmParam(int type, uint64_t duration, uint32_t mode = 0, uint64_t interval_time = 0);

    int readKeys(KeyBroad &keys);
    KeyBroad dealKeysTime(uint8_t key, uint64_t nullTime, uint64_t keyTime);

    int initAntswith(uint8_t mode);

public:
    /**
     * @brief 初始化iio
     * @param ip    k100的ip
     * @param mode  产品模式,参考ProductType
     * @return IIO_Registers*
     */
    static IIO_Registers *initIIORegister(std::string ip, uint8_t mode);

    /**
     * @brief 回收iio
     * @return IIO_Registers*
     */
    static IIO_Registers *deleteIIORegister();

    /**
     * @brief 按键识别
     * @param callback 传入回调函数
     */
    void initKeys(CallbackFunction callback);

    /**
     * @brief 停止按键识别
     */
    void killKeys();

    /**
     * @brief Set the Buzzer Level object
     * @param level 等级 0~15
     * @return int 返回值 0失败 1成功
     */
    int setBuzzerLevel(int level);

    /**
     * @brief Set the Light Level object
     * @param level 等级 0~15
     * @return int 返回值 0失败 1成功
     */
    int setLightLevel(int level);

    /**
     * @brief Set the Buzzer Alarm object
     * @param _switch true开启 false停止
     * @param seconds 时长，单位s
     * @param mode  模式参考AlarmMode
     * @return int  返回值 0失败 1成功
     */
    int setBuzzerAlarm(bool _switch, uint64_t seconds = 0, uint8_t mode = 0);

    /**
     * @brief Set the Motor Alarm object
     * @param _switch true开启 false停止
     * @param duration 时长，单位s
     * @param mode 模式参考MotorMode
     * @param interval_time 当mode处于M_INTERVAL(间歇告警)时,传入间歇时间 单位ms
     * @return int 返回值 0失败 1成功
     */
    int setMotorAlarm(bool _switch, uint64_t duration = 0, uint32_t mode = 0, uint64_t interval_time = 0);

    /**
     * @brief Set the Led Alarm object
     * @param _switch true开启 false停止
     * @param seconds 时长，单位s
     * @param mode 模式参考AlarmMode
     * @return int 返回值 0失败 1成功
     */
    int setLedAlarm(bool _switch, uint64_t seconds = 0, uint8_t mode = 0);

    /**
     * @brief Set the Antswith object
     * @param freq 频点值
     * @return int 0失败 1成功
     */
    int setAntswith(int freq);

    int setControlIIO(uint8_t bit, uint8_t value); // bit 控制哪个引脚 value 置0还是置1
    int getControlIIO(uint8_t bit);                // 获取bit位

    // void performCallback(CallbackFunction callback);
};

#endif // !_IIO_REGISTER_H_