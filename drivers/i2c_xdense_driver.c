/**
 * @file    i2c_xdense_driver.cpp
 * @brief   Library for the I2C in XDense SAMD21 boards
 * @author  Pedro Santos (pjsol@isep.ipp.pt)
 *
 * @copyright	This code is public domain but you buy me a beer if you use
 * this and we meet someday (Beerware license).
 *
 * TODO: description
 *
 */

#include "i2c_xdense_driver.h"


void config_I2C(void){
    i2c_m_sync_get_io_descriptor(&I2C_0, &I2C_io);
    //i2c_m_sync_set_baudrate(&I2C_0, 0, 400000);
    i2c_m_sync_enable(&I2C_0);
}





void Wire_begin(){

}

void Wire_beginTransmission(uint8_t addr){
	i2c_m_sync_set_slaveaddr(&I2C_0, addr, I2C_M_SEVEN);
}

uint8_t Wire_endTransmission(){
	return 0;
}

size_t Wire_write(uint8_t val){
	//i2c_m_sync_write(&I2C_0, &val, 1);
	io_write(I2C_io, &val, 1);
	return 1;
}

int Wire_available(){
	return 1;
}

int Wire_read(){
	int val;
	io_read(I2C_io, &val, 1);
	//i2c_m_sync_read(I2C_io, &val, 1);
	return val;
}

uint8_t Wire_requestFrom(uint8_t address, uint8_t * buff,  size_t quantity){
	i2c_m_sync_cmd_read(&I2C_0, address, buff, quantity);
	return quantity;
}





// /**
//  * @brief Configures I2C communications and initializes registers to defaults
//  *
//  * @return True if initialized successfully. False otherwise.
//  */
// void APDS9960_init(){
// 	/* Read ID register and check against known values for APDS-9960 */
// 	printf("\r\ni2c_m_sync_set_slaveaddr...\n");
// 	i2c_m_sync_set_slaveaddr(&I2C_0, APDS9960_I2C_ADDR, I2C_M_SEVEN);
// 	printf("\r\ni2c_m_sync_set_slaveaddr... OK\n");
// 	printf("\r\ni2c_m_sync_cmd_read...\n");


// 	//io_write(I2C_io, APDS9960_ID, 1);
// 	//delay_ms(1000);
// 	//n = io_read(I2C_io, buff, 1);
// 	i2c_m_sync_cmd_read(&I2C_0, APDS9960_ID, buff, 1);
// 	printf("\r\ni2c_m_sync_cmd_read... OK\n");
// 	printf("Addr= %d , should be: %d or %d\n", buff[0], APDS9960_ID_1, APDS9960_ID_2);
// }
