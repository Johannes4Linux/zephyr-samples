/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_NODELABEL(myled)

#define STACKSIZE 512
#define PRIORITY 7

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

void led_thread(void)
{
	int ret;

	if (!gpio_is_ready_dt(&led)) {
		return;
	}

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return;
	}

	while (1) {
		gpio_pin_toggle_dt(&led);
		k_msleep(250);
	}
}

void print_thread(void)
{
	while (1) {
		printf("Greetings, my friend\n");
		k_msleep(1000);
	}
}

K_THREAD_DEFINE(led_id, STACKSIZE, led_thread, NULL, NULL, NULL,
		PRIORITY, 0, 0);
K_THREAD_DEFINE(print_id, STACKSIZE, print_thread, NULL, NULL, NULL,
		PRIORITY, 0, 0);
