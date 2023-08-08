#include <stdio.h>
#include "IIORegister.h"
#include <bitset>

void getkeys(KeyBroad &keys)
{
    printf("main key:%d value:%d\n", keys.key, keys.value);
}

int main()
{
    IIO_Registers *iio;
    iio = IIO_Registers::initIIORegister("ip:192.168.100.233");

    // uint32_t aa = 0;
    // std::cout << "value1:" << std::bitset<32>(aa) << std::endl;
    // aa |= 0xff;
    // std::cout << "value2:" << std::bitset<32>(aa) << std::endl;
    // aa &= ~(0xff);
    // std::cout << "value3:" << std::bitset<32>(aa) << std::endl
    //           << std::endl;

    // 开关板控制
    // iio->setAntSwitch(0x01);

    // 键盘控制
    iio->initKeys(getkeys);

    int level = 0;

    while (1)
    {
        // led调试
        // iio->setLedAlarm(true, 2, 200);
        // sleep(1);
        // iio->setLedAlarm(true, 5, 100);
        // sleep(2);

        // iio->setLedAlarm(false);

        // 蜂鸣器调试
        // iio->setBuzzerAlarm(true, 2, 30);
        // sleep(1);
        // // iio->setBuzzerAlarm(true, 2, B_SHORT);
        // // sleep(1);
        // if (level >= 6)
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
        // iio->setLightLevel(15);
        // level++;
        // sleep(2);

        // 获取位
        // std::cout << "but0:" << iio->getControlIIO(0) << std::endl;
        // sleep(2);

        // iio->performCallback(getkeys);
        sleep(1);
    }

    return 0;
}