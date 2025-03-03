#include "encodermode.hpp"


namespace peripheral{
    EncoderMode::EncoderMode(TIM_HandleTypeDef* htim, uint32_t channel)
     : htim_(htim), channel_(channel) ,period_(htim_->Init.Period + 1){
        std::unique_ptr<TIM_Encoder_InitTypeDef> sConfig = std::make_unique<TIM_Encoder_InitTypeDef>();
        //ENCODERMODEの読み取り
        if( (htim_->Instance->SMCR & TIM_SMCR_SMS) == TIM_ENCODERMODE_TI1){
            edge_ = 2;
        }else if((htim_->Instance->SMCR & TIM_SMCR_SMS) == TIM_ENCODERMODE_TI2){
            edge_ = 2;
        }else if((htim_->Instance->SMCR & TIM_SMCR_SMS) == TIM_ENCODERMODE_TI12){
            edge_ = 4;
        }
     }
    void EncoderMode::Start(){
        HAL_TIM_Encoder_Start(htim_, channel_);
    }

    void EncoderMode::ReadVal(){
        count_ =  __HAL_TIM_GET_COUNTER(htim_);
        //std::cout << "count_:" << count_ << std::endl;
    }

    void EncoderMode::Stop(){
        HAL_TIM_Encoder_Stop(htim_, channel_);
    }

    void EncoderMode::Reset(){
        this->set_val(30000);
    }

    uint32_t EncoderMode::get_val(){
        return count_;
    }

    void EncoderMode::set_val(float count){
        //count_ = count;
        __HAL_TIM_SET_COUNTER(htim_,(uint32_t)count);
    }

}