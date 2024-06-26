#include "leds.h"
#include <Arduino.h>


int leerleds(int16_t teclaled){
    int val = !digitalRead(teclaled);
    return val;
}