#include "leds.h"
#include <Arduino.h>

volatile int8_t current_led_index = 0;  // Índice del LED actual
volatile int8_t current_direction = 1;  // Dirección actual
volatile uint16_t previousMillis = 0;  // Variable para almacenar el tiempo anterior
volatile uint16_t tiempo_encendido = 500; // Tiempo de encendido por defecto


// Función para encender un LED
void activar_led(uint8_t* LED) {
    digitalWrite(LED, HIGH);
}

// Función para apagar todos los LEDs excepto uno
void desactivar_leds(uint8_t* LED) {
    for (int i = 0; i < 4; ++i) {
        if (leds[i].LED != LED) {
            digitalWrite(leds[i].LED, LOW);
        }
    }
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

// Función para cambiar el LED
void cambiarLed() {
    current_led_index += current_direction;  // Indica la direccion inicial (+1)

    if (current_led_index > 3) {
        current_led_index = 0;
    } else if (current_led_index < 0) {
        current_led_index = 3;
    }

    // Encender el siguiente LED
    activar_led(leds[current_led_index].LED);
    // Apagar los demás LEDs
    desactivar_leds(leds[current_led_index].LED);
}
