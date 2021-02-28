/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "application.h"

//Device    Flash size Number of pages Page size Start Address
//SAMD21x18 256Kbytes  4096            64 bytes  0x00000000

static uint8_t page_data[64];

void application_log_debug(const char* function, const char* message_type, const char* msg){
    #ifdef APPLICATION_DEBUG
        printf("[%s] [APPLICATION] [%s] %s\n", message_type, function, msg);
    #endif
}

void application_reboot_into_bootloader(int boot_port_select){
    //Reboot into bootloader
    application_log_debug(__FUNCTION__, "OK", "Rebooting into bootloader now...");
    switch(boot_port_select){
        case PORT_E:
            BOOT_PORT_SELECTED_DATA = BOOT_PORT_SELECT_UART_E;
        break;
        case PORT_S:
            BOOT_PORT_SELECTED_DATA = BOOT_PORT_SELECT_UART_S;
        break;
        case PORT_W:
            BOOT_PORT_SELECTED_DATA = BOOT_PORT_SELECT_UART_W;
        break;
        case PORT_N:
            BOOT_PORT_SELECTED_DATA = BOOT_PORT_SELECT_UART_N;
        break;
        case PORT_D:
            BOOT_PORT_SELECTED_DATA = BOOT_PORT_SELECT_UART_DBG;
        break;
        default:
            application_log_debug(__FUNCTION__, "WARNING", "Wrong boot_port_select. PORT DBG selected.");
            BOOT_PORT_SELECTED_DATA = BOOT_PORT_SELECT_UART_DBG;
        break;
    }    
    BOOT_DOUBLE_TAP_DATA = DOUBLE_TAP_MAGIC;
    NVIC_SystemReset();
    while (true);//I wont loop here much, only until the chip gets reset
    return;
}

void application_reboot(){
    application_log_debug(__FUNCTION__, "OK", "Rebooting now...");
    NVIC_SystemReset();
    while (true);//I wont loop here much, only until the chip gets reset
    return;
}

void application_boot_mode_command_send(struct usart_sync_descriptor *const UART_descr){
    usart_sync_set_baud_rate(UART_descr, 65536 - ((65536 * 16.0f * 115200) / 48000000 )); // CONF_GCLK_SERCOM3_CORE_FREQUENCY));
    delay_us(50);
    io_write(&(UART_descr->io), (char *) "R", 2);
}

void application_program_neigboor_command_send(struct usart_sync_descriptor *const UART_descr){
    usart_sync_set_baud_rate(UART_descr, 65536 - ((65536 * 16.0f * 115200) / 48000000 )); // CONF_GCLK_SERCOM3_CORE_FREQUENCY));
    delay_us(50);
    io_write(&(UART_descr->io), (char *) "P", 2);
}

void programNeighboringNode(){
    application_boot_mode_command_send(&UART_E);
    delay_ms(2000);
    flasher_programNeighboringNode(&UART_E);
    delay_ms(1000);
    application_program_neigboor_command_send(&UART_E);
}