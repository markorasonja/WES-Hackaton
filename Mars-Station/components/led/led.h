/**
 * @file led.h
 *
 * @brief See the source file.
 *
 * COPYRIGHT NOTICE: (c) 2024 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

#ifndef __LED_C__
#define __LED_C__

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------- INCLUDES ----------------------------------
#include "esp_err.h"

#define DELAY_TIME_ON_MS_BASIC  (800U)
#define DELAY_TIME_OFF_MS_BASIC (200U)

#define DELAY_TIME_ON_MS_SOS    (100U)
#define DELAY_TIME_OFF_MS_SOS   (100U)

//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------
/**
 * @brief Enums hold all board LEDs.
 *
 */
typedef enum
{
    LED_BLUE,
    LED_RED,
    LED_COUNT
} led_t;

//---------------------- PUBLIC FUNCTION PROTOTYPES --------------------------
/**
 * @brief The function initializes LED.
 *
 * @param [in] led LED instance (e.g. LED_BLUE).
 *
 * @return esp_err_t ESP_OK on success, fail otherwise.
 */
esp_err_t led_init(led_t led);

/**
 * @brief The function turns LED on.
 *
 * @param [in] led LED instance (e.g. LED_BLUE).
 *
 * @return esp_err_t ESP_OK on success, fail otherwise.
 */
esp_err_t led_on(led_t led);

/**
 * @brief The function turns LED off.
 *
 * @param [in] led LED instance (e.g. LED_BLUE).
 *
 * @return esp_err_t ESP_OK on success, fail otherwise.
 */
esp_err_t led_off(led_t led);

/**
 * @brief The function shows the led pattern.
 *
 * @param [in] led LED instance (e.g. LED_BLUE).
 *
 * @return esp_err_t ESP_OK on success, fail otherwise.
 */
esp_err_t led_pattern_show(led_t led);


/**
 * @brief The function shows the led pattern for marsquake.
 *
 * @param [in] led1 LED instance (e.g. LED_BLUE).
 * 
 * @param [in] led2 LED instance (e.g. LED_BLUE).
 *
 * @return esp_err_t ESP_OK on success, fail otherwise.
 */
esp_err_t led_earthquake_pattern_show(led_t led1, led_t led2);

#ifdef __cplusplus
}
#endif

#endif // __LED_C__
