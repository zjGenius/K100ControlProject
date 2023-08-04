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

#include "SDR/context.h"
#include "SDR/device.h"

struct AlarmThread
{
    std::atomic_bool running; // 线程是否运行
    std::thread thread_;      // 线程
    uint64_t duration;        // 告警时长
    int mode;                 // 告警模式
    uint64_t startTime;       // 告警启动事件
    uint64_t interval_time;   // 告警间隔时间
};

struct KeyBroad
{
    uint8_t key;   // 哪个键值
    uint8_t value; // 状态 1短 2长
};

struct KeyBroad_TM
{
    uint8_t old_key; //
    uint64_t press_tm = 0;
    uint64_t release_tm = 0;
};

enum BuzzerMode
{
    B_SHORT = 100,    // 100ms
    B_MODERATE = 300, // 300ms
    B_LONG = 500      // 500ms
};
enum MotorMode
{
    M_SUSTAIN, // 持续震
    M_INTERVAL // 间歇震
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

typedef void (*CallbackFunction)(KeyBroad &);
class IIO_Registers
{
private:
    Context *pCtx = nullptr;
    Device *pDev = nullptr;

    KeyBroad_TM key_timer;

    AlarmThread buzzerThread; // 蜂鸣器
    AlarmThread motorThread;  // 马达
    AlarmThread ledThread;    // led
    AlarmThread keysThread;   // 按键

private:
    void _buzzer_thread(uint64_t seconds, uint32_t mode);
    void _led_thread(uint64_t seconds, uint32_t mode);
    void _motor_thread(uint64_t seconds, uint32_t mode, uint64_t interval_time = 0);
    void _keyBroadIIO_thread(CallbackFunction callback);
    void _keyBroadEvent_thread();

    void setAlarmBit(uint32_t command);
    void resetAlarmBit(uint32_t command);
    void writeAlarmBit(uint8_t bit, uint32_t value);
    int getAlarmBit(uint8_t a);

    uint32_t getAlarmBit(int type);
    void setAlarmParam(int type, uint64_t duration, uint32_t mode, uint64_t interval_time = 0);

    int readKeys(KeyBroad &keys);
    KeyBroad dealKeysTime(uint8_t key, uint64_t nullTime, uint64_t keyTime);

public:
    IIO_Registers();
    ~IIO_Registers();
    int initIIO(std::string ip);
    // void initKeys(void *(int key, int type)); // 回调函数
    void initKeys(CallbackFunction callback);
    void killKeys();

    int setBuzzerLevel(int level);
    int setLightLevel(int level);

    int setBuzzerAlarm(bool _switch, uint64_t seconds = 0, uint32_t mode = 0);
    int setMotorAlarm(bool _switch, uint64_t duration = 0, uint32_t mode = 0, uint64_t interval_time = 0);
    int setLedAlarm(bool _switch, uint64_t seconds = 0, uint32_t mode = 0);

    int setControlIIO(uint8_t bit, uint8_t value); // bit 控制哪个引脚 value 置0还是置1
    int getControlIIO(uint8_t bit);

    bool setAntSwitch(uint32_t value);

    void performCallback(CallbackFunction callback);

    std::thread::id _led_thread_id();
};

#endif // !_IIO_REGISTER_H_