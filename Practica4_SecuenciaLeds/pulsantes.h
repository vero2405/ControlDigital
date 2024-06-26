#ifndef __PULSANTES_H
#define __PULSANTES_H

#include <stdint.h>
#include "hal.h"

typedef enum {
    ESTADO_INICIAL,
    ESTADO_UP,
    ESTADO_FALLING,
    ESTADO_DOWN,
    ESTADO_RISING
} estado_t;

typedef struct {
    int pin;
    estado_t estadoActual;
    unsigned long previousMillis;
} switch_t;

bool leeSW(int16_t sw);
bool valSW(int16_t sw);
void inicializarMEF(switch_t* sw);
void DetectorDurante40ms(switch_t* sw);
void actualizarMEF(switch_t* sw);

#endif