#ifndef _IMU_HPP_
#define _IMU_HPP_

#include <memory>
#include <iostream>
#include <cstdint>

#include "config.h"
#include "spi.hpp"
#include "states.hpp"
#include "consts.hpp"

namespace sensor{
    class IIMU{

    public:
        IIMU() = default;
        virtual void Init() = 0;
        virtual void ReadVal() = 0;
        virtual void ReadRaw() = 0;
        virtual void GetOffset() = 0;
        virtual std::unique_ptr<state::Motion>& get_val_ref() = 0;
        virtual std::unique_ptr<state::Motion>& get_raw_ref() = 0;
        virtual ~IIMU() = default;

    };

    class ICM20689 : public IIMU{
    private:
        std::unique_ptr<peripheral::SPI> spi_;
        std::unique_ptr<state::Motion> val_;
        std::unique_ptr<state::Motion> raw_;
        std::unique_ptr<state::Motion> offset_;
		float AccelRead(uint8_t H_reg) ;
		float OmegaRead(uint8_t H_reg) ;
    public:
        ICM20689(std::unique_ptr<peripheral::SPI> spi, 
        std::unique_ptr<state::Motion> val,
        std::unique_ptr<state::Motion> raw,
        std::unique_ptr<state::Motion> offset);
		void Init() override ;
        void ReadRaw() override ;
        void GetOffset() override ;
		void ReadVal() override ;
        std::unique_ptr<state::Motion>& get_val_ref() override;
        std::unique_ptr<state::Motion>& get_raw_ref()override;
        virtual ~ICM20689() = default;
    };
    
}

#endif // _IMU_HPP_