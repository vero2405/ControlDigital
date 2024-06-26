#include "pulsantes.h"
#include <Arduino.h>

int leerTecha(int16_t tecla){
    int val = !digitalRead(tecla);
    return val;
}