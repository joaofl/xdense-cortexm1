/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   application.h
 * Author: joao
 *
 * Created on July 11, 2017, 6:09 PM
 */

#ifndef APPLICATION_H
#define APPLICATION_H

#include "utils.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "driver_init.h"
#include "flasher.h"

#ifdef __cplusplus
extern "C" {
#endif

#define APPLICATION_DEBUG

void application_reboot_into_bootloader(int boot_port_select);
void application_reboot();
void programNeighboringNode();

#ifdef __cplusplus
}
#endif

#endif /* APPLICATION_H */

