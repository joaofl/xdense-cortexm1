/**
 * @file    i2c_xdense_driver.h
 * @brief   Library for the I2C in XDense SAMD21 boards
 * @author  Pedro Santos (pjsol@isep.ipp.pt)
 *
 * @copyright	This code is public domain but you buy me a beer if you use
 * this and we meet someday (Beerware license).
 *
 * TODO: description
 *
 */


#ifndef I2C_XDENSE_DRIVER_H
#define I2C_XDENSE_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "atmel_start.h"

struct io_descriptor *I2C_io;

void config_I2C(void);



void 	Wire_begin();
void 	Wire_beginTransmission(uint8_t addr);
size_t 	Wire_write(uint8_t val);
int 	Wire_available();
int 	Wire_read();
uint8_t Wire_requestFrom(uint8_t address, uint8_t * buff,  size_t quantity);




#ifdef __cplusplus
}
#endif

#endif /* I2C_XDENSE_DRIVER_H */
