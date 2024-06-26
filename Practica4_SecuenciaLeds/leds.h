#ifndef __LEDS_H
#define __LEDS_H

#include <stdint.h>
#include "hal.h"
#include "pulsantes.h"


// Estructura para representar los leds
typedef struct {
    uint8_t LED;
    bool estado;
} control_leds;

control_leds leds[] = {
    {LED_GREEN, false},
    {LED_YELLOW, false},
    {LED_RED, false},
    {LED_BLUE, false}
};

void activar_led(uint8_t* LED);
void desactivar_leds(uint8_t* LED);
bool activar_sw(uint8_t* SW);
void cambiarLed();

#endif