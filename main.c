#include <atmel_start.h>
//#include "xdense/router.h"
#include "xdense/terminal.h"
#include "xdense/sensors.h"
#include "drivers/i2c_xdense_driver.h"
#include "drivers/apds9960.h"

//static uint8_t pck_tx[PCK_SIZE] = "0000000000000000";

//Delare timer tasks structure
static struct timer_task task_terminal;

static void task_terminal_cb(const struct timer_task *const timer_task)
{
    terminal_read();
}

void init_tasks(void)
{
    task_terminal.interval = 100;
    task_terminal.cb       = task_terminal_cb;
    task_terminal.mode     = TIMER_TASK_REPEAT;

    timer_add_task(&TIMER_0, &task_terminal);
}

uint8_t proximity_data = 0;

int main(void) {
    uint16_t ambient_light = 0;
    uint16_t red_light = 0;
    uint16_t green_light = 0;
    uint16_t blue_light = 0;

    uint8_t proximity_data = 0;

    /* Initializes MCU, drivers and middleware */
    init_tasks();
    atmel_start_init();
    printf("\nSystem initialized...\n");


    printf("\n\rAPDS9960_init...\n\r");
    printf("APDS9960_init = %d", APDS9960_init());
    APDS9960_setProximityGain(PGAIN_2X);
    printf("\n\rAPDS9960_init... OK\n\r");

    if ( APDS9960_enableProximitySensor(false) ) {
        printf("Proximity sensor is now running\n\r");
    } else {
        printf("Something went wrong during sensor init!\n\r");
    }

    if ( APDS9960_enableLightSensor(false) ) {
      printf("Light sensor is now running\n\r");
    } else {
      printf("Something went wrong during light sensor init!\n\r");
    }

    // if ( APDS9960_enableGestureSensor(false) ) {
    //   printf("Gesture sensor is now running\n\r");
    // } else {
    //   printf("Something went wrong during gesture sensor init!\n\r");
    // }

    uint8_t i = 0;
    while (1) {

        if (!APDS9960_readAmbientLight(&ambient_light) ||
            !APDS9960_readRedLight(&red_light) ||
            !APDS9960_readGreenLight(&green_light) ||
            !APDS9960_readBlueLight(&blue_light) ) {
            printf("Error reading light values\n\r");
        }
        else {
            printf("Ambient: %d  Red: %d Green: %d Blue: %d\n\r", (int) ambient_light, (int) red_light, (int) green_light, (int) blue_light);
        }

        if ( !APDS9960_readProximity(&proximity_data) ) {
            printf("Error reading proximity value\n\r");
        } else {
            printf("Proximity: %d\n\r", proximity_data);
        }

        // if ( APDS9960_isGestureAvailable() ) {
        //   switch ( APDS9960_readGesture() ) {
        //     case DIR_UP:
        //       printf("UP\n\r");
        //       break;
        //     case DIR_DOWN:
        //       printf("DOWN\n\r");
        //       break;
        //     case DIR_LEFT:
        //       printf("LEFT\n\r");
        //       break;
        //     case DIR_RIGHT:
        //       printf("RIGHT\n\r");
        //       break;
        //     case DIR_NEAR:
        //       printf("NEAR\n\r");
        //       break;
        //     case DIR_FAR:
        //       printf("FAR\n\r");
        //       break;
        //     default:
        //       printf("NONE\n\r");
        //   }
        // }



        //APDS9960_readProximity(&proximity_data);
        //printf("Proximity data= %d\n", proximity_data);
        gpio_toggle_pin_level(LED);
        delay_ms(1000);
    }
}
