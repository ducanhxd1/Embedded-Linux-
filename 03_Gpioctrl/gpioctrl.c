#include <linux/module.h>
#include <linux/init.h>
#include <linux/gpio.h>         // For the GPIO functions

static struct gpio_desc *led_gpio, *button_gpio;

#define IO_LED 21
#define IO_BUTTON 20

#define IO_OFFSET 0

static int __init my_init(void)
{
    int status;
    led_gpio = gpio_to_desc(IO_LED + IO_OFFSET);

    if (!led_gpio) {
        printk("gpio_to_desc failed for LED GPIO %d\n", IO_LED + IO_OFFSET);
        return -ENODEV;
    }

    button_gpio = gpio_to_desc(IO_BUTTON + IO_OFFSET);
    if (!button_gpio) {
        printk("gpio_to_desc failed for Button GPIO %d\n", IO_BUTTON + IO_OFFSET);
        gpiod_put(led_gpio);
        return -ENODEV;
    }

    status = gpiod_direction_output(led_gpio, 0);
    if (status) {
        printk("gpiod_direction_output failed for LED GPIO\n");
        return status;
    }

    status = gpiod_direction_input(button_gpio);
    if (status) {
        printk("gpiod_direction_input failed for Button GPIO\n");
        return status;
    }

    gpiod_set_value(led_gpio, 1); // Turn on the LED
    printk("gpioctrl - Buttons is %s pressed\n", gpiod_get_value(button_gpio) ? "": "not ");

    return 0;
}

static void __exit my_exit(void)
{
    gpiod_set_value(led_gpio, 0); // Turn off the LED
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("GPIO Control Driver");
MODULE_AUTHOR("Duc Anh");
MODULE_VERSION("1.0");