#include "interrupt.hpp"

namespace peripheral{

    IT* IT::instances_[MAX_INSTANCES] = { nullptr };

    IT* IT::Find(TIM_HandleTypeDef* htim){
        for(uint32_t i = 0; i < MAX_INSTANCES; i++){
            if(instances_[i] != nullptr && instances_[i]->get_htim() == htim){
                return instances_[i];
            }
        }
        return nullptr;
    }

    IT::IT(TIM_HandleTypeDef* htim):htim_(htim){
        this-> Register();
    }

    void IT::Register(){
        for(uint32_t i = 0; i < MAX_INSTANCES; i++){
            if(instances_[i] == nullptr){
                instances_[i] = this;
                break;
            }
        }
    }

    HAL_StatusTypeDef IT::Start() {
        return HAL_TIM_Base_Start_IT(htim_);
    }

    void IT::Callback(){ //DIの適用ポイント
        printf("Callback\n");

    }

    HAL_StatusTypeDef IT::Stop(){
        return HAL_TIM_Base_Stop_IT(htim_);
    }


    extern "C" void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
        //受け取ったhtimを元にインスタンスを探す
        IT* it = IT::Find(htim);
        if(it != nullptr){
            it->Callback();
        }

    }

}
