/**
 * @file ic74hc595.h
 * @author Jaime Albuquerque (jaime.albq@gmail.com)
 * @brief Output serializer
 * @version 0.1
 * @date 2022-09-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#if !defined(_ic74hc595_H_)
#define _ic74hc595_H_

#if defined(IDF_VER) // Settings for ESP-IDF

#include <stdlib.h>

#include "driver/gpio.h"
#include "esp32/rom/ets_sys.h"

#define SETPIN(PIN)     gpio_set_level(PIN, 1)
#define CLRPIN(PIN)     gpio_set_level(PIN, 0)
#define _DELAY_US(x)    ets_delay_us(x)

#endif // IDF_VER

typedef struct {
	unsigned char num_reg;		// Number of shift registers
	unsigned char *reg_value;	// Last value of the registers

	// GPIO
	struct pin {
		
#if defined(IDF_VER)
		gpio_num_t clk;
		gpio_num_t signal;
		gpio_num_t latch;
#endif // IDF_VER

	} pin;
} ic74hc595_t;

/**
 * @brief Initialize the microcontroller to do the output
 * 
 * @param shft 
 * @return < 0 means error
 */
signed char ic74hc595_init(ic74hc595_t *shft);

/**
 * @brief Send the whole data
 * 
 * @param data 
 * @param len 
 * @param shft 
 * @return signed char 
 */
signed char ic74hc595_send(char *data, unsigned char len, ic74hc595_t *shft);

/**
 * @brief Send 1 byte at a time
 * 
 * @param data 
 * @param shft 
 * @return signed char 
 */
signed char ic74hc595_send8bits(char data, ic74hc595_t *shft);

/**
 * @brief Latch the registers
 * 
 * @param shft 
 * @return signed char 
 */
signed char ic74hc595_latch(ic74hc595_t *shft);

#endif // _ic74hc595_H_
