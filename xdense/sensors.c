/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "sensors.h"


int8_t n = 0;
uint8_t buff[10]={0};
uint8_t addr = 0;

struct io_descriptor *I2C_io;

// void config_sensors(void){
//     i2c_m_sync_get_io_descriptor(&I2C_0, I2C_io);
//     i2c_m_sync_enable(&I2C_0);
// }

uint32_t read_humidity(void){

    i2c_m_sync_set_slaveaddr(&I2C_0, addr, I2C_M_SEVEN);
    n = io_read(I2C_io, buff, 1);
    printf("addr=%d n=%d\n", addr, n);

            addr++;
    if (addr==128)
        addr=0;
}

/* APDS-9960 I2C address */
//#define APDS9960_I2C_ADDR       0x39

//#define APDS9960_ID             0x92

/* Acceptable device IDs */
//#define APDS9960_ID_1           0xAB
//#define APDS9960_ID_2           0x9C
