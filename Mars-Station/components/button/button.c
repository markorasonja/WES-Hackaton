#include "button.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>
#include <esp_event.h>
#include "led.h"

//---------------------------------- MACROS -----------------------------------
#define GPIO_BUTTON_1 (36U)
#define GPIO_BUTTON_2 (32U)
#define GPIO_LED_BLUE    (14U)
#define GPIO_BIT_MASK(X) ((1ULL << (X)))
// #define GPIO_LED_GREEN   (27U)

#define DELAY_TIME_MS (1000U)


//-------------------------------- DATA TYPES ---------------------------------
/**
 * @brief Pointer to the function that will be called on button press.
 *
 * @param [in] p_arg Pointer to the users custom argument.
 *
 */
typedef void (*button_pressed_isr_t)(void *p_arg);

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------
/**
 * @brief Callback function for button 1 press.
 *
 * @param [in] p_arg Pointer to the pin that caused the callback.
 */
static void _btn_1_isr(void *p_arg);

/**
 * @brief Callback function for button 2 press.
 *
 * @param [in] p_arg Pointer to the pin that caused the callback.
 */
static void _btn_2_isr(void *p_arg);

/**
 * @brief The function initializes button and its interrupt service routine.
 *
 * @param pin Pin to which the button is connected to.
 * @param p_isr Pointer to the ISR that will be executed on button press.
 * @return esp_err_t ESP_OK on success, fail otherwise.
 */
static esp_err_t _button_init(uint8_t pin, button_pressed_isr_t p_isr);


static void IRAM_ATTR _btn_1_isr(void *p_arg)
{
    (void)p_arg; /* Suppress the unused variable warning*/

    led_pattern_show(LED_BLUE);
}

static void IRAM_ATTR _btn_2_isr(void *p_arg)
{
    (void)p_arg; /* Suppress the unused variable warning*/

    led_earthquake_pattern_show(LED_BLUE, LED_RED);
}


static esp_err_t _button_init(uint8_t pin, button_pressed_isr_t p_isr)
{
    // Configure the GPIO.
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << pin),
        .mode         = GPIO_MODE_INPUT,
        .pull_up_en   = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type    = (GPIO_INTR_POSEDGE),
    };

    esp_err_t esp_err = gpio_config(&io_conf);

    if(ESP_OK == esp_err)
    {
        // Change gpio interrupt type for a pin.
        esp_err = gpio_set_intr_type(io_conf.pin_bit_mask, io_conf.intr_type);
    }

    if(ESP_OK == esp_err)
    {
        // Install gpio isr service.
        gpio_install_isr_service(ESP_INTR_FLAG_LEVEL3);
        /* esp_err is not assigned to it because it returns invalid
        statuses when called many times (for many buttons)*/
    }

    if(ESP_OK == esp_err)
    {
        // Hook isr handler for specific gpio pin.
        esp_err = gpio_isr_handler_add(pin, p_isr, (void *)&pin);
    }

    return esp_err;
}


void buttons_init()
{
    _button_init(GPIO_BUTTON_1, _btn_1_isr);
    _button_init(GPIO_BUTTON_2, _btn_2_isr);
}