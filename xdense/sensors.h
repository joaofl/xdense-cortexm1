/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   sensors.h
 * Author: joao
 *
 * Created on August 2, 2017, 6:58 PM
 */

#ifndef SENSORS_H
#define SENSORS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "atmel_start.h"
//#include "drivers/i2c_xdense_driver.h"
//#include <math.h>


//void config_sensors(void);
uint32_t read_humidity(void);
//void APDS9960_init();


#ifdef __cplusplus
}
#endif

#endif /* SENSORS_H */
