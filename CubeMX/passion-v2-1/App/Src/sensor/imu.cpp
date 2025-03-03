#include "imu.hpp"

namespace sensor{
    ICM20689::ICM20689(std::unique_ptr<peripheral::SPI> spi,
    std::unique_ptr<state::Motion> val,std::unique_ptr<state::Motion> raw,
    std::unique_ptr<state::Motion> offset)
        : spi_(std::move(spi)), val_(std::move(val)), raw_(std::move(raw)), offset_(std::move(offset)){}

    
    float ICM20689::AccelRead(uint8_t H_reg) {
    int16_t data = (int16_t)(((uint8_t)spi_->ReadByte(H_reg) << 8) |
                                (uint8_t)spi_->ReadByte(H_reg + 1));
    float accel = (float)(data / 2048.0f)*consts::physics::G*consts::physics::M2MM; //[mm/s^2] FS_SEL=3-> Scale Factor=2048[LSB/(g)]
    return accel;
	}

    float ICM20689::OmegaRead(uint8_t H_reg) {
    int16_t data = (int16_t)(((uint8_t)spi_->ReadByte(H_reg) << 8) |
                                (uint8_t)spi_->ReadByte(H_reg + 1));
    float omega =
        (float)(data / 16.4f); //[deg/s] FS_SEL=3-> Scale Factor=16.4[LSB/(dps)]
    return omega;
	}
    
    void ICM20689::Init(){
        //初期化処理
        uint8_t who_am_i = 0;
		who_am_i = spi_->ReadByte(0x75);              // check WHO_AM_I (0x75)
		printf("who_am_i = 0x%x\r\n", who_am_i); // Who am I = 0x98

		if (who_am_i != 0x98) { // recheck 0x98
			HAL_Delay(100);
			who_am_i = spi_->ReadByte(0x98);
			if (who_am_i != 0x98) {
				printf("gyro_error\r\n\n");
				while (1) {
				}
			}
		}

		// PWR_MIGHT_1 0x6B
		spi_->WriteByte(0x6B, 0x00); // Set pwr might
		HAL_Delay(50);
		// PWR_MIGHT_2 0x6C
		spi_->WriteByte(0x6C, 0x00);
		HAL_Delay(50);
		// set gyro config
		// GYRO_CONFIG 0x1B
		spi_->WriteByte(0x1B, 0x18); // use 2000 dps
		HAL_Delay(50);
		// ACCEL_CONFIG 0x1C
		spi_->WriteByte(0x1B, 0x18); // use pm 16g
		HAL_Delay(50);
        
    }

    void ICM20689::ReadRaw(){
        raw_->accel[static_cast<int>(state::Motion::AXIS::X)] = -1 * this->AccelRead(0x3B);
		raw_->accel[static_cast<int>(state::Motion::AXIS::Y)] = this->AccelRead(0x3D);
		raw_->accel[static_cast<int>(state::Motion::AXIS::Z)] = this->AccelRead(0x3F);
		raw_->omega[static_cast<int>(state::Motion::AXIS::X)] = this->OmegaRead(0x43);
		raw_->omega[static_cast<int>(state::Motion::AXIS::Y)] = this->OmegaRead(0x45);
		raw_->omega[static_cast<int>(state::Motion::AXIS::Z)] = this->OmegaRead(0x47);
    }

    void ICM20689::GetOffset(){
        //オフセット取得
        this->ReadRaw();
        std::unique_ptr<state::Motion>& raw = this->get_raw_ref();
        offset_->accel[static_cast<int>(state::Motion::AXIS::X)] = raw->accel[static_cast<int>(state::Motion::AXIS::X)];
        offset_->accel[static_cast<int>(state::Motion::AXIS::Y)] = raw->accel[static_cast<int>(state::Motion::AXIS::Y)];
        offset_->accel[static_cast<int>(state::Motion::AXIS::Z)] = raw->accel[static_cast<int>(state::Motion::AXIS::Z)];
        offset_->omega[static_cast<int>(state::Motion::AXIS::X)] = raw->omega[static_cast<int>(state::Motion::AXIS::X)];
        offset_->omega[static_cast<int>(state::Motion::AXIS::Y)] = raw->omega[static_cast<int>(state::Motion::AXIS::Y)];
        offset_->omega[static_cast<int>(state::Motion::AXIS::Z)] = raw->omega[static_cast<int>(state::Motion::AXIS::Z)];
    }

    void ICM20689::ReadVal(){
        this->ReadRaw();
        std::unique_ptr<state::Motion>& raw = this->get_raw_ref();
        val_->accel[static_cast<int>(state::Motion::AXIS::X)] = raw->accel[static_cast<int>(state::Motion::AXIS::X)] - offset_->accel[static_cast<int>(state::Motion::AXIS::X)];
        val_->accel[static_cast<int>(state::Motion::AXIS::Y)] = raw->accel[static_cast<int>(state::Motion::AXIS::Y)] - offset_->accel[static_cast<int>(state::Motion::AXIS::Y)];
        val_->accel[static_cast<int>(state::Motion::AXIS::Z)] = raw->accel[static_cast<int>(state::Motion::AXIS::Z)] - offset_->accel[static_cast<int>(state::Motion::AXIS::Z)];
        val_->omega[static_cast<int>(state::Motion::AXIS::X)] = raw->omega[static_cast<int>(state::Motion::AXIS::X)] - offset_->omega[static_cast<int>(state::Motion::AXIS::X)];
        val_->omega[static_cast<int>(state::Motion::AXIS::Y)] = raw->omega[static_cast<int>(state::Motion::AXIS::Y)] - offset_->omega[static_cast<int>(state::Motion::AXIS::Y)];
        val_->omega[static_cast<int>(state::Motion::AXIS::Z)] = raw->omega[static_cast<int>(state::Motion::AXIS::Z)] - offset_->omega[static_cast<int>(state::Motion::AXIS::Z)];        
    }

    std::unique_ptr<state::Motion>& ICM20689::get_val_ref(){
        return val_;
    }

    std::unique_ptr<state::Motion>& ICM20689::get_raw_ref(){
        return raw_;
    }


}