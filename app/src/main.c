/** \file main.c */

#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>

#define LED_NODE DT_CHOSEN(app_led)
#if !DT_NODE_EXISTS(LED_NODE)
#error "Missing /chosen node 'app-led'."
#endif

// Showing some more `devicetree.h` usage: The following compile time switch leads to a proper
// error message for the unlikely scenario where a referenced `gpio` node has the status "disabled".
// Such a compile-time switch is not typically used in an application and exists only for
// demonstrational purposes in the matching article.
#if DT_NODE_HAS_STATUS(DT_PHANDLE(LED_NODE, gpios), okay)
/*
 * The LED node's GPIO device specification. This information uses the property "gpios",
 * which is of type `phandle-array`, where each phandle receives the `pin` and `flags` as metadata.
 * Each field in the GPIO specification is in the end set using the `DT_PHA_BY_IDX` that we've
 * seen in the devicetree semantics.
 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);
#else
#error "The status of the GPIO referenced by the LED node is not 'okay'"
#endif

#define LED_NODE DT_CHOSEN(app_led)
#if !DT_NODE_EXISTS(LED_NODE)
#error "Missing /chosen node 'app-led'."
#endif

/*
 * The `status` property is not defined in the devicetree for our LED node. Any node without a
 * `status` property is implicitly assumed to have the status "okay". Thus, the following
 * condition evaluates to `false`, no error occurs. Such compile-time checks are pretty common
 * within Zephyr and help to reduce the code size and RAM consumption of the final application.
 */
#if !DT_NODE_HAS_STATUS(LED_NODE, okay)
#error "LED node status is not okay."
#endif

#define SLEEP_TIME_MS 1000U

void main(void)
{
    int err   = 0;
    bool tick = true;

    if (!gpio_is_ready_dt(&led))
    {
        printk("Error: LED pin is not available.\n");
        return;
    }

    err = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    if (err != 0)
    {
        printk("Error %d: failed to configure LED pin.\n", err);
        return;
    }

    while (1)
    {
        (void) gpio_pin_toggle_dt(&led);
        k_msleep(SLEEP_TIME_MS);
        if (tick != false)
        {
            printk("Tick\n");
        }
        else
        {
            printk("Tock\n");
        }
        tick = !tick;
    }
}
