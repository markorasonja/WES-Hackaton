/**
 * @file main.c
 *
 * @brief
 *
 * COPYRIGHT NOTICE: (c) team StackOverflow
 * All rights reserved.
 */

//--------------------------------- INCLUDES ----------------------------------
//#include "user_interface.h"
#include "led.h"
#include "hat_sensor.h"
#include "wifi.h"
#include "mqtt-mars.h"
// #include "button.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>


void app_main(void)
{
    /* button init, led init, wifi init, sensor init, mqtt init, gui init */
    // user_interface_init();
    led_init(LED_BLUE);
    led_init(LED_RED);
    // (void) buttons_init();
    (void) wifi_init();
    (void) sht31_init();
    (void) start_reading();
    // vTaskStartScheduler();
}
