/*テストしたら全部のインスタンス捨てる*/
#ifndef TEST_HPP_
#define TEST_HPP_

#include <memory>
#include <iostream>
#include <cstdint>

#include "config.h"
#include "adc.hpp"
#include "eeprom.hpp"
#include "encodermode.hpp"
#include "gpio.hpp"
#include "interrupt.hpp"
#include "pwm.hpp"
#include "spi.hpp"
#include "wait.hpp"
#include "buzzer.hpp"
#include "led.hpp"
#include "imu.hpp"
#include "states.hpp"

    class Test{
    private:
        std::unique_ptr<peripheral::ADC> adc_;
        std::unique_ptr<peripheral::EEPROM> eeprom_;
        std::unique_ptr<peripheral::EncoderMode> encodermode_;
        std::unique_ptr<peripheral::GPIO> gpio_;
        std::unique_ptr<peripheral::IT> interrupt_;
        std::unique_ptr<peripheral::PWM> pwm_;
        std::unique_ptr<peripheral::SPI> spi_;
        std::unique_ptr<peripheral::Wait> wait_;
        std::unique_ptr<indicator::Buzzer> buzzer_;
        std::unique_ptr<indicator::LED> led_;
        std::unique_ptr<sensor::IIMU> imu_;

    public:
        Test() = default;
        void LED();
        void Buzzer();
        void IMU();
        ~Test() = default;
    };


#endif /* TEST_HPP_ */
