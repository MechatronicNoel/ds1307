/*
 * ds1307.h
 *
 *  Created on: Sep 17, 2021
 *      Author: nooee
 */

#ifndef DS1307_H_
#define DS1307_H_

#include "i2c.h"
#include "DBG.h"
void start_i2c_scan(I2C_HandleTypeDef *I2Chnd, uint32_t delay_);



#endif /* DS1307_H_ */
