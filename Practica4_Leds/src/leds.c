#include "../inc/leds.h"
#include "../inc/hal.h"
#include <Arduino.h>

control_leds leds[] ={
    {LED_GREEN, false},
    {LED_YELLOW, false},
    {LED_RED, false},
    {LED_BLUE, false}
};

volatile int8_t actual_led_index = 0;  // Índice del LED actual
volatile int8_t actual_direction = 1;  // Dirección actual
volatile uint16_t previousMillis = 0;  // Variable para almacenar el tiempo anterior
volatile uint16_t tiempo_encendido = 500; // Tiempo de encendido por defecto


// Función para encender un LED
bool activar_led(uint8_t LED) {
    digitalWrite(LED, HIGH);
    return true;
}

// Función para apagar todos los LEDs excepto uno
void desactivar_leds(uint8_t LED) {
    for (int i = 0; i < 4; ++i) {
        if (leds[i].LED != LED) {
            digitalWrite(leds[i].LED, LOW);
        }
    }
}

// Función para cambiar el LED
void cambiarLed() {
    actual_led_index += actual_direction;  // Indica la direccion inicial (+1)

    if (actual_led_index > 3) {
        actual_led_index = 0;
    } else if (actual_led_index < 0) {
        actual_led_index = 3;
    }

    // Encender el siguiente LED
    activar_led(leds[actual_led_index].LED);
    // Apagar los demás LEDs
    desactivar_leds(leds[actual_led_index].LED);
}
