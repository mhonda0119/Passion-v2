#include "test.hpp"

void Test::LED(){

    std::array<std::unique_ptr<peripheral::GPIO>, 7> leds {
        std::make_unique<peripheral::GPIO>(LED_1_GPIO_Port, LED_1_Pin),
        std::make_unique<peripheral::GPIO>(LED_2_GPIO_Port, LED_2_Pin),
        std::make_unique<peripheral::GPIO>(LED_3_GPIO_Port, LED_3_Pin),
        std::make_unique<peripheral::GPIO>(LED_4_GPIO_Port, LED_4_Pin),
        std::make_unique<peripheral::GPIO>(LED_5_GPIO_Port, LED_5_Pin),
        std::make_unique<peripheral::GPIO>(LED_6_GPIO_Port, LED_6_Pin),
        std::make_unique<peripheral::GPIO>(LED_7_GPIO_Port, LED_7_Pin),
    };

    indicator::LED led(std::move(leds));

    //on,offのテスト
    for(int i = 1; i <= 7; ++i){
        led.On(i);
        HAL_Delay(100);
        led.Off(i);
    }
    //toggleのテスト
    for(int i = 1; i <= 8; ++i){
        led.Toggle(i);
        HAL_Delay(100);
        led.Toggle(i);
    }

    /*作成した全部のインスタンスを破棄*/
    leds.~array();
    led.~LED();

}

void Test::Buzzer(){

    std::unique_ptr<peripheral::PWM> pwm = std::make_unique<peripheral::PWM>(&htim3, TIM_CHANNEL_2);
    indicator::Buzzer buzzer(std::move(pwm));

    //start,stopのテスト
    buzzer.Start(700, 80);
    HAL_Delay(1000);
    buzzer.Stop();

    HAL_Delay(500);

    //playのテスト
    buzzer.Play(1000, 1000, 80);

    /*作成したインスタンスを破棄*/
    pwm.~unique_ptr();
    buzzer.~Buzzer();

}
z
void Test::IMU(){
    
    std::unique_ptr<peripheral::SPI> spi = std::make_unique<peripheral::SPI>(&hspi3,GPIOD,CS_Pin);
    std::unique_ptr<state::Motion> val = std::make_unique<state::Motion>();
    std::unique_ptr<state::Motion> raw = std::make_unique<state::Motion>();
    std::unique_ptr<state::Motion> offset = std::make_unique<state::Motion>();
    std::unique_ptr<sensor::IIMU> imu = std::make_unique<sensor::ICM20689>(std::move(spi), std::move(val), std::move(raw), std::move(offset));

    imu.Init();
    imu.ReadRaw();
    imu.GetOffset();
    imu.ReadVal();

    for(int i = 0; i < 10; ++i){
        std::cout << imu.get_val_ref()->accel[i] << std::endl;
        std::cout << imu.get_raw_ref()->accel[i] << std::endl;
        HAL_Delay(100);
    }

    /*作成したインスタンスを破棄*/
    spi.~unique_ptr();
    val.~unique_ptr();
    raw.~unique_ptr();
    offset.~unique_ptr();
    imu.~ICM20689();
}