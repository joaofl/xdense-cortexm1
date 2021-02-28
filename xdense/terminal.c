#include "terminal.h"

void terminal_read(void)
{   
    uint8_t pck_received[PCK_SIZE];
    //TODO: improve this terminal
    if (usart_sync_is_rx_not_empty(&UART_DBG)){
        uint8_t c = getc(stdin);
        switch(c){
            case 'r':
                application_reboot();
                break;
            case 'R':
                application_reboot_into_bootloader(PORT_D);
                break;
            case 'P':
                programNeighboringNode();
                break;
            case 'G':
                if(ringbuffer_xdense_get_packet(&ringback_descr_RX_E, pck_received, PCK_SIZE) != ERR_NONE){
                    printf(" ERROR ringbuffer_xdense_get_packet\n");
                } else {
                    printf(" OK ringbuffer_xdense_get_packet\n");
                }
                printf("packet: ");
                for (int i = 0; i < PCK_SIZE; i++)
                    putc(pck_received[i], stdout);        
                printf("\n");
                break;
            case 'h':
                printf("[HELP] Commands available are:\n"
                        "P - Program Neighbor Node:\n"
                        "h - Show this help\n"
                        "r - Reboot\n"
                        "R - Reboot into the bootloader\n"
                        );
                break;
            default:
                printf("No action associated with '%c' (press 'h' for help).\n", c);
                break;
        }
    }
}