/*
2020 David DiPaola
Licensed under CC0
*/

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

int
main(void) {
	rcc_clock_setup_in_hse_8mhz_out_72mhz();

	rcc_periph_clock_enable(RCC_GPIOC);
	gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);
	gpio_set(GPIOC, GPIO13);

	for (;;) {
		for (int i=0; i<200000l; i++) {
			__asm__("nop");
		}

		gpio_toggle(GPIOC, GPIO13);
	}
}
