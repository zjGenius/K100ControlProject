
/**
 * @file main.cpp
 * @author zhangjun (zhangjun.sole@qq.com)
 * @brief K100控制外设示例程序
 * @version 0.1
 * @date 2023-08-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#include "IIORegister.h"
// #include <bitset>

/**
 * @brief 回调函数 获取按键
 * 
 * @param keys 
 */
void getkeys(KeyBroad &keys)
{
    printf("main key:%d value:%d\n", keys.key, keys.value);
}

int main()
{
    IIO_Registers *iio = new IIO_Registers();
    if (iio->initIIO("ip:192.168.100.233") == 0)
    {
        printf("IIO init failed.\n");
        return -1;
    }
    int level = 0;

    // 开关板控制
    // iio->setAntSwitch(0x01);

    // 键盘控制
    iio->initKeys(getkeys);

    while (1)
    {
        // led调试
        // iio->setLedAlarm(true, 2, B_LONG);
        // sleep(1);
        // iio->setLedAlarm(true, 2, B_SHORT);
        // sleep(1);

        // 蜂鸣器调试
        // iio->setBuzzerAlarm(true, 2, B_LONG);
        // sleep(1);
        // iio->setBuzzerAlarm(true, 2, B_SHORT);
        // sleep(1);
        // if (level >= 5)
        //     level = 0;
        // iio->setBuzzerLevel(level);
        // level++;

        // 马达调试
        // iio->setMotorAlarm(true, 5, M_INTERVAL, 200);
        // sleep(3);
        // iio->setMotorAlarm(true, 5, M_SUSTAIN);
        // sleep(3);

        // 屏幕亮度调节
        // if (level >= 15)
        //     level = 0;
        // iio->setLightLevel(level);
        // level++;
        // sleep(2);

        // 获取位
        // std::cout << "but0:" << iio->getControlIIO(0) << std::endl;
        // sleep(2);

        sleep(1);
    }

    return 0;
}
