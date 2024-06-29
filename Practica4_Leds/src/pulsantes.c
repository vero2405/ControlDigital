#include "../inc/pulsantes.h"
#include "../inc/hal.h"
#include <Arduino.h>

control_pulsadores pulsadores[] = {
    {SW1, false}, // SW1
    {SW2, false}, // SW2
    {SW3, false}, // SW3
    {SW4, false} // SW4
};

void inicializarMEF(switch_t* sw) {
    sw->estadoActual = ESTADO_INICIAL;
    sw->previousMillis = 0;
    pinMode(sw->pin, INPUT_PULLUP);
}

void DetectorDurante40ms(switch_t* sw) {
    unsigned long currentMillis = millis();
    if (currentMillis - sw->previousMillis >= 40) {
        sw->previousMillis = currentMillis;  // Actualizar el tiempo anterior    
        int val = digitalRead(sw->pin);
        if(val == HIGH) {  // activamos el flag
            sw->estadoActual = ESTADO_UP;
        } else {
            sw->estadoActual = ESTADO_DOWN;
        }
    }
}
switch_t switches[] = {
    {SW1, ESTADO_INICIAL, 0},
    {SW2, ESTADO_INICIAL, 0},
    {SW3, ESTADO_INICIAL, 0},
    {SW4, ESTADO_INICIAL, 0}
};

void actualizarMEF(switch_t* sw) {
    int val = digitalRead(sw->pin);
    
    switch (sw->estadoActual) {
    case ESTADO_INICIAL:
        if (val == HIGH) {
            sw->estadoActual = ESTADO_UP;
        } else {
            sw->estadoActual = ESTADO_DOWN;
        }
        break;
        
    case ESTADO_UP:
        sw->estadoActual = ESTADO_FALLING;
        break;
        
    case ESTADO_DOWN:
        sw->estadoActual = ESTADO_RISING;
        break;
        
    case ESTADO_FALLING:
        DetectorDurante40ms(sw);
        break;
        
    case ESTADO_RISING:
        DetectorDurante40ms(sw);
        break;
        
    default:
        inicializarMEF(sw);
        break;
    }
}

