/**
 * @file led.c
 *
 * @brief This file controls LEDs.
 *
 * COPYRIGHT NOTICE: (c) 2024 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

//--------------------------------- INCLUDES ----------------------------------
#include "led.h"
#include "driver/gpio.h"
#include <stdio.h>
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

//---------------------------------- MACROS -----------------------------------
#define DELAY_TIME_EARTHQUAKE (250U)
#define DELAY_ON_BASIC        (800U)
#define DELAY_OFF_BASIC       (200U)


#define GPIO_BIT_MASK(X)  ((1ULL << (X)))

//-------------------------------- DATA TYPES ---------------------------------
/**
 * @brief LED config structure.
 *
 */
typedef struct
{
    led_t  led;
    int8_t gpio;
    bool   b_is_active_on_high_level;
} _led_config_t;

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------

//------------------------- STATIC DATA & CONSTANTS ---------------------------
static const _led_config_t _led_info[LED_COUNT] = {
    { .led = LED_BLUE, .gpio = 14, .b_is_active_on_high_level = true },
    { .led = LED_BLUE, .gpio = 26, .b_is_active_on_high_level = true }
};
//------------------------------- GLOBAL DATA ---------------------------------

//------------------------------ PUBLIC FUNCTIONS -----------------------------
esp_err_t led_init(led_t led)
{
    esp_err_t esp_err = ESP_OK;

    if(led < LED_COUNT)
    {
        /* Zero-initialize the config structure. */
        gpio_config_t io_conf = {};
        /* Disable interrupt. */
        io_conf.intr_type = GPIO_INTR_DISABLE;
        /* Set as output. */
        io_conf.mode = GPIO_MODE_OUTPUT;
        /* Bit mask of the pins that you want to set,e.g.GPIO18/19. */
        io_conf.pin_bit_mask = GPIO_BIT_MASK(_led_info[led].gpio);
        /* Disable internal pull-down. */
        io_conf.pull_down_en = 0;
        /* Disable internal pull-up. */
        io_conf.pull_up_en = 0;
        /* Configure GPIO with the given settings. */
        gpio_config(&io_conf);
    }
    else
    {
        esp_err = ESP_FAIL;
    }

    return esp_err;
}

esp_err_t led_on(led_t led)
{
    esp_err_t esp_err = ESP_FAIL;

    if(led < LED_COUNT)
    {
        /* Figure out if the LED will turn on after outputting 1 or 0. */
        uint32_t level = _led_info[led].b_is_active_on_high_level ? 1U : 0U;

        esp_err = gpio_set_level(_led_info[led].gpio, level);
    }

    return esp_err;
}

esp_err_t led_off(led_t led)
{
    esp_err_t esp_err = ESP_FAIL;

    if(led < LED_COUNT)
    {
        /* Figure out if the LED will turn off after outputting 1 or 0. */
        uint32_t level = _led_info[led].b_is_active_on_high_level ? 0U : 1U;

        esp_err = gpio_set_level(_led_info[led].gpio, level);
    }

    return esp_err;
}


esp_err_t led_pattern_show(led_t led)
{
    // int i;
    esp_err_t esp_err;
    for (int i=0; i<5; i++)
    {
        esp_err = led_on(led);
        vTaskDelay(DELAY_ON_BASIC / portTICK_PERIOD_MS);
        esp_err = led_off(led);
        vTaskDelay(DELAY_OFF_BASIC / portTICK_PERIOD_MS);
    }

    return esp_err;
}

esp_err_t led_earthquake_pattern_show(led_t led1, led_t led2)
{
    // int i;
    esp_err_t esp_err;
    for (int i=0; i<5; i++)
    {
        esp_err = led_on(led1);
        vTaskDelay(DELAY_TIME_EARTHQUAKE / portTICK_PERIOD_MS);
        esp_err = led_off(led2);
        vTaskDelay(DELAY_TIME_EARTHQUAKE / portTICK_PERIOD_MS);

        esp_err = led_off(led1);
        vTaskDelay(DELAY_TIME_EARTHQUAKE / portTICK_PERIOD_MS);
        esp_err = led_on(led2);
        vTaskDelay(DELAY_TIME_EARTHQUAKE / portTICK_PERIOD_MS);
    }

    return esp_err;
}

