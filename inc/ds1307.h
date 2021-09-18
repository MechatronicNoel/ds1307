/**
 * @copyright (c) 2021 Noel Dom https://www.youtube.com/channel/UCINCDcQylATh2wS5BAYIBPg.
 *
 * @brief	Device Driver for DS1307 Real-time clock (RTC)
 * @file	ds1307.h
 * @version 0.1.0
 * @date	2021
 * @author 	Noel Dominguez.
 */
#ifndef DS1307_H_
#define DS1307_H_

#include "i2c.h"
#include "DBG.h"

typedef struct {

	uint8_t seconds;
	uint8_t minutes;
	uint8_t hours;
	uint8_t day;
	uint8_t date;
	uint8_t month;
	uint8_t year;

}ds1307_dev_t;


typedef enum{
	DS1307_OK,
	DS1307_ERROR
}ds1307_err_t;


/**
 * @brief I2C Scanner utility .
 *
 * @param[in]	I2Chnd: i2c handler
 * @param[in]	delay_: delay between each device scan
 *
 */
void start_i2c_scan(I2C_HandleTypeDef *I2Chnd, uint32_t delay_);
void ds1307_init(void);
ds1307_err_t ds1307_set_hour(uint8_t hour);
uint8_t ds1307_get_hour(void);
ds1307_err_t ds1307_set_hour(uint8_t hour);
void ds1307_set_clock_halt(uint8_t halt);
uint8_t ds1307_get_clock_halt(void);
void ds1307_set_second(uint8_t second);
uint8_t ds1307_get_second(void);
void ds1307_set_minutes(uint8_t minutes);
uint8_t ds1307_get_minutes(void);


#endif /* DS1307_H_ */
