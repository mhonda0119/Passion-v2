#include "led.hpp"

namespace indicator{
    LED::LED(std::array<std::unique_ptr<peripheral::GPIO>, 7> leds) 
        : led_(std::move(leds)){}

    void LED::On(uint8_t num){
        switch(num){
            case 1:
                led_[0] -> On();
                break;
            case 2:
                led_[1] -> On();
                break;
            case 3:
                led_[2] -> On();
                break;
            case 4:
                led_[3] -> On();
                break;
            case 5:
                led_[4] -> On();
                break;
            case 6:
                led_[5] -> On();
                break;
            case 7:
                led_[6] -> On();
                break;
            case 8:
                for(int i = 0; i < 7; i++){
                    led_[i] -> On();
                }
                break;
            default:
                break;
        }
    }

    void LED::Off(uint8_t num){
        switch(num){
            case 1:
                led_[0] -> Off();
                break;
            case 2:
                led_[1] -> Off();
                break;
            case 3:
                led_[2] -> Off();
                break;
            case 4:
                led_[3] -> Off();
                break;
            case 5:
                led_[4] -> Off();
                break;
            case 6:
                led_[5] -> Off();
                break;
            case 7:
                led_[6] -> Off();
                break;
            case 8:
                for(int i = 0; i < 7; i++){
                    led_[i] -> Off();
                }
                break;
            default:
                break;
        }
    }

    void LED::Toggle(uint8_t num){
        switch(num){
            case 1:
                led_[0] -> Toggle();
                break;
            case 2:
                led_[1] -> Toggle();
                break;
            case 3:
                led_[2] -> Toggle();
                break;
            case 4:
                led_[3] -> Toggle();
                break;
            case 5:
                led_[4] -> Toggle();
                break;
            case 6:
                led_[5] -> Toggle();
                break;
            case 7:
                led_[6] -> Toggle();
                break;
            case 8:
                for(int i = 0; i < 7; i++){
                    led_[i] -> Toggle();
                }
                break;
            default:
                break;
        }
    }
} // namespace indicator