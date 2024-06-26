#include <Arduino.h>
#include <stdint.h>
#include <stdbool.h>


extern "C"{
    #include "hal.h"
    #include "leds.h"
    #include "pulsantes.h"
}


////
void setup() {
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_YELLOW, OUTPUT);
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);
    pinMode(SW1, INPUT_PULLUP);
    pinMode(SW2, INPUT_PULLUP);
    pinMode(SW3, INPUT_PULLUP);
    pinMode(SW4, INPUT_PULLUP);
  
    // Encender el LED_GREEN al iniciar
    activar_led(LED_GREEN);
}

void loop() {
    volatile uint16_t currentMillis = millis();  // Obtener el tiempo actual en milisegundos
    
    // Verificar si se presionó SW1
    if (activar_sw(SW1)) { // Cambia la dirección
        current_direction = -1;
    }
    
    // Verificar si se presionó SW2
    if (activar_sw(SW2)) { // Cambia a la dirección inicial (Resetea)
        current_direction = 1;
    }
    
    // Verificar si se presionó SW3
    if (activar_sw(SW3)) { // Cambia el tiempo de encendido a 200 ms
        tiempo_encendido = 200;
    }
    
    // Verificar si se presionó SW4
    if (activar_sw(SW4)) { //Cambia el tiempo de encendido a 750 ms
        tiempo_encendido = 750;
    }
    
    // Cambiar el LED cada tiempo_encendido ms
    if (currentMillis - previousMillis >= tiempo_encendido) {
        previousMillis = currentMillis;  // Actualizar el tiempo anterior
        cambiarLed();  // Cambiar el LED
    }
}

////

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

