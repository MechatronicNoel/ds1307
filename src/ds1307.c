/**
 * @copyright (c) 2021 Noel Dom https://www.youtube.com/channel/UCINCDcQylATh2wS5BAYIBPg.
 *
 * @brief	Device Driver for DS1307 Real-time clock (RTC)
 * @file	ds1307.c
 * @version 0.1.0
 * @date	2021
 * @author 	Noel Dominguez.
 */


#include "ds1307.h"

#define DS1307_ADDRES		0x68
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


#define DS1307_HANDLER		hi2c1

typedef enum{
	DS1307_1HZ,
	DS1307_4096HZ,
	DS1307_8192HZ,
	DS1307_32768HZ
}ds1307_rate_t;



static ds1307_err_t ds1307_write_byte(uint8_t ds1307_reg_addres, uint8_t data);
static uint8_t ds1307_read_byte(uint8_t ds1307_reg_addres);
static uint8_t ds1307_bcd(uint8_t data);


static ds1307_err_t ds1307_write_byte(uint8_t ds1307_reg_addres, uint8_t data){

	uint8_t buff[2] = {ds1307_reg_addres,data};
	ds1307_err_t ret_val;
	ret_val = HAL_I2C_Master_Transmit(&DS1307_HANDLER, DS1307_ADDRES << 1, buff, 2, DS1307_TIMEOUT);

	return ret_val;
}

static uint8_t ds1307_read_byte(uint8_t ds1307_reg_addres){

	uint8_t data;
	HAL_I2C_Master_Transmit(&DS1307_HANDLER, DS1307_ADDRES << 1, &ds1307_reg_addres, 1, DS1307_TIMEOUT);
	HAL_I2C_Master_Receive(&DS1307_HANDLER, DS1307_ADDRES << 1, &data, 1, DS1307_TIMEOUT);
	return data;
}

static uint8_t ds1307_bcd(uint8_t data){
	return (((data & 0xf0) >> 4) * 10) + (data & 0x0f);
}


void ds1307_init(void){
	ds1307_set_clock_halt(0);
}


void ds1307_set_clock_halt(uint8_t halt){
	uint8_t ch = (halt ? 1 << 7 : 0);
	ds1307_write_byte(DS1307_SECONDS, ch | (ds1307_read_byte(DS1307_SECONDS) & 0x7F));
}

uint8_t ds1307_get_clock_halt(void){
	return (ds1307_read_byte(DS1307_SECONDS) & 0x80) >> 7;
}


ds1307_err_t ds1307_set_hour(uint8_t hour){
	return ds1307_write_byte(DS1307_HOURS,ds1307_bcd(hour & 0x3F));
}

uint8_t ds1307_get_hour(void){
	return ds1307_bcd (ds1307_read_byte(DS1307_HOURS) & 0x3F);
}


void ds1307_set_second(uint8_t second){
	uint8_t val = ds1307_get_clock_halt();
	ds1307_write_byte(DS1307_SECONDS, ds1307_bcd(second | val));

}

uint8_t ds1307_get_second(void){
	return ds1307_bcd(ds1307_read_byte(DS1307_SECONDS) & 0x7F);
}

void ds1307_set_minutes(uint8_t minutes){
	ds1307_write_byte(DS1307_MINUTES, ds1307_bcd(minutes));
}

uint8_t ds1307_get_minutes(void){
	return ds1307_read_byte(ds1307_bcd(DS1307_MINUTES));
}

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
