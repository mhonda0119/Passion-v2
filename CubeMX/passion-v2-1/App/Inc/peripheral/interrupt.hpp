#ifndef _INTERRUPT_HPP_
#define _INTERRUPT_HPP_

#include <iostream>
#include <memory>
#include <cstdint>
#include "config.h"
#include "stdout.h"


namespace peripheral{
	class IT{
		private:
		TIM_HandleTypeDef* htim_;
		static constexpr uint32_t MAX_INSTANCES = 4;
		static IT* instances_[MAX_INSTANCES];

		public:
		IT(TIM_HandleTypeDef* htim);
		void Register(); // instanceの登録
		TIM_HandleTypeDef* get_htim() const { return htim_; }
		HAL_StatusTypeDef Start();
        void Callback(); // 修正: 戻り値の型を追加
		HAL_StatusTypeDef Stop();
		static IT* Find(TIM_HandleTypeDef* htim);
		~IT() = default;
	};
}

#endif /* _INTERRUPT_HPP_ */