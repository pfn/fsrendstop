#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "pico/binary_info.h"

const uint LED_PIN = 25;
const uint ENDSTOP_PIN = 2;

void trigger_endstop(bool triggered) {
    if (triggered) {
        gpio_put(LED_PIN, 0);
        gpio_set_dir(ENDSTOP_PIN, GPIO_IN);
    } else {
        gpio_put(LED_PIN, 1);
        gpio_set_dir(ENDSTOP_PIN, GPIO_OUT);
        gpio_put(ENDSTOP_PIN, 0);
    }
}
int main() {
    bi_decl(bi_program_description(
         "FSR endstop for auto Z offset calibration."));
    bi_decl(bi_1pin_with_name(LED_PIN, "On-board LED"));
    stdio_init_all();
    adc_init();

    gpio_init(LED_PIN);
    gpio_init(ENDSTOP_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    adc_gpio_init(26);

    // Select ADC input 0 (GPIO26)
    adc_select_input(0);
    trigger_endstop(false);

    uint16_t last_value;

    while (1) {
        uint16_t result = adc_read();

        if (abs(last_value - result) > 75) {
            last_value = result;
            printf("ADC reading: %d\n", result);
            trigger_endstop(result > 200);
        }
    }
}

