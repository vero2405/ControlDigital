#include <Arduino.h>
#include <stdint.h>
#include <stdbool.h>

#include "../inc/hal.h"
#include "../inc/leds.h"
#include "../inc/pulsantes.h"

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
    volatile uint16_t currentMillis = millis();
    
    // Presiona SW1: Cambia la dirección
    if (activar_sw(SW1)) {
        actual_direction = -1;
    }
    
    // Presiona SW2: Cambia a dirección inicial (Resetea)
    if (activar_sw(SW2)) {
        actual_direction = 1;
    }
    
    // Presiona SW3: Cambia el tiempo de encendido a 200 ms
    if (activar_sw(SW3)) {
        tiempo_encendido = 200;
    }
    
    // Presiona SW4: Cambia el tiempo de encendido a 750 ms
    if (activar_sw(SW4)) {
        tiempo_encendido = 750;
    }
    
    // Tiempo de encendido para cada led
    if (currentMillis - previousMillis >= tiempo_encendido) {
        previousMillis = currentMillis;  // Actualizar el tiempo anterior
        cambiarLed();  // Cambiar el LED
    }
}