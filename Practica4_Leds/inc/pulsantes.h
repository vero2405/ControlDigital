#ifndef __PULSANTES_H
#define __PULSANTES_H

#include <stdint.h>
#include "hal.h"


// Estructura para representar los pulsadores
typedef struct {
    uint8_t SW;
    bool activacion;
} control_pulsadores;

control_pulsadores pulsadores[] = {
    {SW1, false}, // SW1
    {SW2, false}, // SW2
    {SW3, false}, // SW3
    {SW4, false} // SW4
};

extern control_pulsadores pulsadores[4];

// Para antirebote mediante Maquina de Estado

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
void inicializarMEF(switch_t* sw);
void DetectorDurante40ms(switch_t* sw);
void actualizarMEF(switch_t* sw);

#endif
