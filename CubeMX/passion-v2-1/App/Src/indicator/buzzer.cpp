#include "buzzer.hpp"

namespace indicator{
    Buzzer::Buzzer(std::unique_ptr<peripheral::PWM> pwm)
     : pwm_(std::move(pwm)) {}

    void Buzzer::Start(uint32_t freq, float duty){
        pwm_->Start();
        pwm_->set_freq(freq);
        pwm_->set_duty(duty);
    }

    void Buzzer::Play(uint32_t freq, uint32_t duration, float duty){
        Start(freq, duty);
        HAL_Delay(duration);
        Stop();
    }

    void Buzzer::Stop(){
        pwm_->Stop();
    }
}
