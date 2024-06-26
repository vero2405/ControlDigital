#include <Arduino.h>
#include <stdint.h>

extern "C" {
    #include "leds.h"
    #include "pulsantes.h"
}

// Estructura para representar los leds
typedef struct {
    uint8_t LED;
    bool estado;
} control_leds;

control_leds leds[] = {
    {LED_GREEN, false},
    {LED_YELLOW, false},
    {LED_RED, false},
    {LED_BLUE, false}
};

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

volatile int8_t current_led_index = 0;  // Índice del LED actual
volatile int8_t current_direction = 1;  // Dirección actual
volatile uint16_t previousMillis = 0;  // Variable para almacenar el tiempo anterior
volatile uint16_t tiempo_encendido = 500; // Tiempo de encendido por defecto


// Función para encender un LED
void activar_led(uint8_t LED) {
    digitalWrite(LED, HIGH);
}

// Función para apagar todos los LEDs excepto uno
void desactivar_leds(uint8_t LED) {
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