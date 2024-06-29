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
