#include "pulsantes.h"
#include <Arduino.h>


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

void actualizarMEF(switch_t* sw) {
    int val = digitalRead(sw->pin);
    static int prevVal = val;
    bool cambio = val ^ prevVal;  // (^: XOR)

    switch (sw->estadoActual) {
    case ESTADO_INICIAL:
        // Inicializar Hardware
        //Serial.print("Estado Inicial - Switch: ");
        //Serial.println(sw->pin);
        if (val == HIGH) {
            sw->estadoActual = ESTADO_UP;
        } else {
            sw->estadoActual = ESTADO_DOWN;
        }
        break;
        
    case ESTADO_UP:
        //Serial.print("Estado UP - Switch: ");
        //Serial.println(sw->pin);
        sw->estadoActual = ESTADO_FALLING;
        break;
        
    case ESTADO_DOWN:
        //Serial.print("Estado DOWN - Switch: ");
        //Serial.println(sw->pin);
        sw->estadoActual = ESTADO_RISING;
        break;
        
    case ESTADO_FALLING:
        //Serial.print("Estado FALLING - Switch: ");
        //Serial.println(sw->pin);
        DetectorDurante40ms(sw);
        break;
        
    case ESTADO_RISING:
        //Serial.print("Estado RISING - Switch: ");
        //Serial.println(sw->pin);
        DetectorDurante40ms(sw);
        break;
        
    default:
        inicializarMEF(sw);
        break;
    }
    prevVal = val;
}