# DS1307 Real-time clock (RTC)
Device driver for DS1307 Real-time clock (RTC) based on _STM32 HAL Library_, What do You need?
- Any STM32 Nucleo-Board or any STM32 Microcontrollers
- STM32Cube IDE (HAL Libraries)
- Any dev-board DS1307 or your custom hardware

## How to use: 
- Created new project in your STM32Cube IDE 
- Select your STM32 Microcontroller in my case I used a STM32F103CBTx (Blue Pill board)
- Select your preferred I2C peripheral in my case I used I2C1 
- If you need to use another I2C peripheral just modify this macro _DS1307_HANDLER_ in the file _ds1307.h_
- Include the source files in your project
- Enjoy!!

## How to contribute to the project?

Submit Merge Requests to fix issues or add features to the repo.

## Schematic Connection


| STM32F103CBT | DS1307 |
|-----------|-----------|
|    PB6    |    SCL    |
|    PB7    |    SDA    |


[![Build Status](https://travis-ci.org/joemccann/dillinger.svg?branch=master)](https://travis-ci.org/joemccann/dillinger)
