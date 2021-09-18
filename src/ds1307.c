/*
 * ds1307.c
 *
 *  Created on: Sep 17, 2021
 *      Author: nooee
 */


#include "ds1307.h"

#define DS1307_SECONDS 		0x00
#define DS1307_MINUTES		0x01
#define DS1307_HOURS		0x02
#define DS1307_DAY			0X03
#define	DS1307_DATE			0x04
#define DS1307_MONTH		0x05
#define	DS1307_YEAR			0x06
#define	DS1307_CONTROL		0x07
#define DS1307_REG_UTC_HR	0x08
#define DS1307_REG_UTC_MIN	0x09
#define DS1307_REG_CENT    	0x10
#define DS1307_REG_RAM   	0x11
#define DS1307_TIMEOUT		1000


#define DS1307_HANDLER		h2ic1

typedef enum{
	DS1307_1HZ,
	DS1307_4096HZ,
	DS1307_8192HZ,
	DS1307_32768HZ
}ds1307_rate_t;

void start_i2c_scan(I2C_HandleTypeDef *I2Chnd, uint32_t delay_){

	HAL_StatusTypeDef status;
	uint8_t no_devices = 0;
	DBG_print("\n\r [ I2C Scanner v0.1 ]");

	for (uint8_t i = 0; i < 128; i++){

		status = HAL_I2C_IsDeviceReady(I2Chnd , (uint16_t)(i<<1), 2, 2);

		if ( status != HAL_OK){
			//DBG_print(".\n\r");
		} else {
			DBG_print("\n\rDevice found! Address: 0x%X",i);
			++no_devices;
		}

		HAL_Delay(delay_);

	}

	if (!no_devices){
		DBG_print("\n\r No Devices found!");
	} else {
		DBG_print("\n\r Total Devices found: %d",no_devices);

	}

}
