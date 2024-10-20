#include <stdio.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/sensor_data_types.h>
#include <zephyr/rtio/rtio.h>
#include <zephyr/dsp/print_format.h>

/*
 * Get a device structure from a devicetree node with compatible
 * "bosch,bme280". (If there are multiple, just pick one.)
 */
const struct device *const dev = DEVICE_DT_GET_ANY(bosch_bme280);

int main(void)
{
	if (!dev) {
		printf("No device found!\n");
	}
	if (!device_is_ready(dev)) {
		printf("device %s is not ready\n", dev->name);
	}

	struct sensor_value temp;

	while(1) {
		sensor_sample_fetch(dev);
		sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &temp);
		printk("temp: %d.%06d\n", temp.val1, temp.val2);
		k_msleep(1000);
	}
	return 0;
}

