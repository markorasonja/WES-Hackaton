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

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>

//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------

//------------------------- STATIC DATA & CONSTANTS ---------------------------

//------------------------------- GLOBAL DATA ---------------------------------

//------------------------------ PUBLIC FUNCTIONS -----------------------------
void app_main(void)
{
    // user_interface_init();
    led_init(LED_BLUE);
    led_pattern_show(LED_BLUE);
}

//---------------------------- PRIVATE FUNCTIONS ------------------------------

//---------------------------- INTERRUPT HANDLERS -----------------------------
