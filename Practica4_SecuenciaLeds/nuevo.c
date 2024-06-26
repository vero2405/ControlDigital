#include <Arduino.h>
#include <stdint.h>

extern "C" {
    #include "leds.h"
    #include "pulsantes.h"
    #include "hal.h"
}


switch_t switches[] = {
    {SW1, ESTADO_INICIAL, 0},
    {SW2, ESTADO_INICIAL, 0},
    {SW3, ESTADO_INICIAL, 0},
    {SW4, ESTADO_INICIAL, 0}
};


void setup() {
    Serial.begin(115200);
    for(int i = 0; i < sizeof(switches) / sizeof(switch_t); i++) {
        inicializarMEF(&switches[i]);
    }
}

void loop() {
    for(int i = 0; i < sizeof(switches) / sizeof(switch_t); i++) {
        actualizarMEF(&switches[i]);
    }
}

