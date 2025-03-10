#ifndef _BUZZER_HPP_
#define _BUZZER_HPP_

#include "pwm.hpp"
#include "config.h"

namespace indicator{
    class Buzzer{
    private:
        uint32_t freq_;
        uint32_t duration;//ms
        std::unique_ptr<peripheral::PWM> pwm_;
    public:
        Buzzer(std::unique_ptr<peripheral::PWM> pwm);//pwm_のインスタンスを注入
        void Start(uint32_t freq,float duty = 80);//指定された周波数で鳴らす
        void Play(uint32_t freq,uint32_t duration,float duty = 20);//指定された周波数，指定された秒数鳴らす
        void Stop();//とめる．
        ~Buzzer() = default;
    };
}

#endif /* _BUZZER_HPP_ */


