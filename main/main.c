#include <stdio.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <driver/gpio.h>

#include "ci74hc595.h"

void app_main(void)
{
        static ci74hc595_t shifter = {
                .num_shft = 1,
                .pin = {
                        .clk = GPIO_NUM_12,
                        .signal = GPIO_NUM_13,
                        .latch = GPIO_NUM_14,
                },
        };


        ci74hc595_init(&shifter);

        while (true) {
                for (uint8_t i = 0; i < 255; i++) {
                        ci74hc595_send8bits(i, &shifter);
                        ci74hc595_latch(&shifter);
                        vTaskDelay(500 / portTICK_RATE_MS);
                }
        }
}
