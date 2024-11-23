/******************************************************************************
* Copyright (C) 2017 - 2022 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/******************************************************************************
 * Engineer    : Brayan Lui Estalla Quinteros
 * Institution : Jicamarca Radio Observatory
 * project     : switch and led
 * Vitis       : 2022.2
 * source:
******************************************************************************/

// Previous status detector on the switch and then displayed on the LEDs
#include "platform.h"
#include "xgpio.h"
#include "xparameters.h"
#include <stdio.h>
#include "xil_printf.h"
#include "sleep.h"

int main() {
    // Pointer declaration
    XGpio led, sw;
    int status;
    int led_value, sw_value, prev_sw_value;

    xil_printf("---initial---\r\n");
    //Initializing GPIOs LED (pointer, id)
    status = XGpio_Initialize(&led, XPAR_LED_DEVICE_ID);

    if (status != XST_SUCCESS) {
        xil_printf("Error initializing led\n");
        return XST_FAILURE;
    }

    // Initializing GPIOs SW (pointer, id)
    status = XGpio_Initialize(&sw, XPAR_SW_DEVICE_ID);

    if (status != XST_SUCCESS) {
        xil_printf("Error initializing sw\n");
        return XST_FAILURE;
    }

    // GPIO LED Configuration (Pointer, Channel, Out-In)
    XGpio_SetDataDirection(&led, 1, 0xF);

    // SW GPIOs configuration (pointer, channel, out-in)
    XGpio_SetDataDirection(&sw, 1, 0x0);

    // Initializing the previous state of the switches
    prev_sw_value = XGpio_DiscreteRead(&sw, 1);

    while (1) {
        // Reading GPIOs SW (pointer, channel)
        sw_value = XGpio_DiscreteRead(&sw, 1);

        // Check for a change in the status of the switches
        if (sw_value != prev_sw_value) {
            led_value = sw_value;

            // Writing GPIOs LEDs (pointer, channel, data)
            XGpio_DiscreteWrite(&led, 1, led_value);
            xil_printf("led : %d\r\n", led_value);

            // Update the previous state of the switches
            prev_sw_value = sw_value;
        }

        //usleep(10000);  // Peque�a pausa para evitar imprimir demasiado r�pido
    }

    return 0;
}




/*
// Read switch and then display the values ​​on the leds
#include "platform.h"
#include "xgpio.h"
#include "xparameters.h"
#include <stdio.h>
#include "xil_printf.h"
#include "sleep.h"


int main() {

	// Pointer declaration
    XGpio led, sw;
    int status;
    int led_value, sw_value;

    xil_printf("---initial---\r\n");
    // Initializing GPIOs LED (pointer, id)
    status = XGpio_Initialize(&led, XPAR_LED_DEVICE_ID);

    if (status != XST_SUCCESS) {
        xil_printf("Error initializing led\n");
        return XST_FAILURE;
    }

    // Initializing GPIOs SW (pointer, id)
    status = XGpio_Initialize(&sw, XPAR_SW_DEVICE_ID);

    if (status != XST_SUCCESS) {
        xil_printf("Error initializing sw\n");
    return XST_FAILURE;
    }

    // GPIO LED Configuration (Pointer, Channel, Out-In)
    XGpio_SetDataDirection(&led, 1, 0xF);

    // SW GPIOs configuration (pointer, channel, out-in)
    XGpio_SetDataDirection(&sw, 1, 0x0);

    while (1) {
    	// Reading GPIOs SW (pointer, channel)
    	sw_value = XGpio_DiscreteRead(&sw, 1);
    	led_value = sw_value;

        // Writing GPIOs SW (pointer, channel, data)
        XGpio_DiscreteWrite(&led, 1, led_value);
        xil_printf("led : %d\r\n", led_value);
        //usleep(10000);
    }

    return 0;
}
*/
