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

extern control_leds leds[];
extern volatile int8_t actual_led_index;
extern volatile int8_t actual_direction;
extern volatile uint16_t previousMillis;
extern volatile uint16_t tiempo_encendido;

bool activar_led(uint8_t LED);
void desactivar_leds(uint8_t LED);
void cambiarLed();

#endif