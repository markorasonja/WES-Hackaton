/**
 * @file hat_sensor.h
 *
 * @brief See the source file.
 *
 * COPYRIGHT NOTICE: (c) 2024 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */
#include "esp_log.h"

#ifndef __HAT_SENSOR_C__
#define __HAT_SENSOR_C__


esp_err_t sht31_init(void);
void start_reading(void);

#endif