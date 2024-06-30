#include <Arduino.h>
#include <stdint.h>
#include <stdbool.h>

#include "../inc/hal.h"
#include "../inc/leds.h"
#include "../inc/pulsantes.h"



bool activar_led(uint8_t LED) {
    digitalWrite(LED, HIGH);
    return true;
}

void desactivar_leds(uint8_t* LED) {
    for (int i = 0; i < 4; ++i) {
        if (leds[i].LED != *LED) {
            digitalWrite(leds[i].LED, LOW);
        }
    }
}

void cambiarLed() {
    actual_led_index += actual_direction;  // Indica la direccion inicial (+1)

    if (actual_led_index > 3) {
        actual_led_index = 0;
    } else if (actual_led_index < 0) {
        actual_led_index = 3;
    }

    activar_led(leds[actual_led_index].LED);
    desactivar_leds(&(leds[actual_led_index].LED));
}

// Función para activar un pulsador
bool activar_sw(uint8_t SW) {
    bool presionado = digitalRead(SW) == LOW;  // Verificar si el pulsador está presionado
    
    for (int i = 0; i < 4; ++i) {
        if (pulsadores[i].SW == SW) {
            pulsadores[i].activacion = presionado;
            //break; // Salir del bucle una vez que se ha encontrado el SW
        } else {
            pulsadores[i].activacion = false;
        }
    }
    
    return presionado;  // Devolver verdadero si el pulsador está presionado
}

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
