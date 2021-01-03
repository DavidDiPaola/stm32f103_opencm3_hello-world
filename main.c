/*
2020,2021 David DiPaola
Licensed under CC0
*/

#include <stdint.h>

#include <libopencm3/stm32/rcc.h>

#include <libopencm3/stm32/gpio.h>

#include <libopencm3/stm32/usart.h>

void
init_led(void) {
	rcc_periph_clock_enable(RCC_GPIOC);

	gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);

	gpio_set(GPIOC, GPIO13);
}

void
init_usart1(uint32_t baud) {
	/*
	UART 1 clock tree: (DS5319 figure 1)
		AHB --> APB2 --> USART 1
	UART 1 pins: (DS5319 table 5)
		TX: GPIO A  9
		RX: GPIO A 10
	*/

	rcc_periph_clock_enable(RCC_GPIOA);

	gpio_set_mode(
		GPIOA,
		GPIO_MODE_OUTPUT_50_MHZ,
		GPIO_CNF_OUTPUT_ALTFN_PUSHPULL,
		GPIO_USART1_TX
	);
	gpio_set_mode(
		GPIOA,
		GPIO_MODE_INPUT,
		GPIO_CNF_INPUT_PULL_UPDOWN,
		GPIO_USART1_RX
	);
	gpio_set(
		GPIOA,
		GPIO10
	);

	rcc_periph_clock_enable(RCC_USART1);
	usart_set_baudrate(USART1, baud);
	usart_set_databits(USART1, 8);
	usart_set_parity(USART1, USART_PARITY_NONE);
	usart_set_stopbits(USART1, 1);
	usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);
	usart_set_mode(USART1, USART_MODE_TX_RX);
	usart_enable(USART1);
}

void
print(const char * str) {
	for (; *str; str++) {
		usart_send_blocking(USART1, *str);
	}
}

int
main(void) {
	rcc_clock_setup_in_hse_8mhz_out_72mhz();

	init_led();

	init_usart1(115200);

	print("hello world!" "\r\n");

	for (;;) {
		for (int i=0; i<800000l; i++) {
			__asm__("nop");
		}

		gpio_toggle(GPIOC, GPIO13);
	}
}
