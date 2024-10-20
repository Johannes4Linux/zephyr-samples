#include <stdio.h>
#include <zephyr/kernel.h>

int main(void)
{
	while (1) {
		printf("Hallo von zephyr RTOS!\n");
		k_msleep(500);
	}
	return 0;
}
