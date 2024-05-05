#include <Arduino.h>
#include <stdint.h>
#include <stdbool.h>

#define LED_GREEN 7
#define LED_YELLOW 6
#define LED_RED 5
#define LED_BLUE 4
#define SW1 2
#define SW2 3
#define SW3 11
#define SW4 12

typedef struct {
    uint8_t pin;
    bool state;
} control_leds;

control_leds leds[] = {
    {LED_GREEN, false},
    {LED_YELLOW, false},
    {LED_RED, false},
    {LED_BLUE, false}
};

volatile uint8_t current_led_index = 1;
volatile uint8_t direction_forward = 1;

void setup() {
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_YELLOW, OUTPUT);
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);
    pinMode(SW1, INPUT_PULLUP);
    pinMode(SW2, INPUT_PULLUP);
    pinMode(SW3, INPUT_PULLUP);
    pinMode(SW4, INPUT_PULLUP);
  
    // Arduino solo tiene 2 interrupciones: Pin 2 (INT0), Pin 3 (INT1)
    // Prioridad al cambio de direccion dado que está en INT0
    attachInterrupt(digitalPinToInterrupt(SW1), cambiodireccion, FALLING);
    attachInterrupt(digitalPinToInterrupt(SW2), resetdireccion, FALLING);

    cli(); // Detiene las interrupciones
  
    // Configurar el TIMER1. Nota: (Timer0: 8bits) - (Timer1: 16bits)
    // OCR1A = (fosc*Ts)/(prescaler) < 65536, fosc = 16 MHz
    *TCCR1A_Ptr = 0;
    *TCCR1B_Ptr = 0;
    *TCNT1_Ptr = 0;
    *OCR1A_Ptr = 3124; // Iniciamos a 200 ms
    *TCCR1A_Ptr |= (1 << WGM12);
    *TCCR1B_Ptr |= (1 << CS12) | (0 << CS11) | (1 << CS10); // prescaler: 1024
    *TIMSK1_Ptr |= (1 << OCIE1A); // habilita comparacion A
    sei();  // Permite las interrupciones
    
    // Encender el primer LED_GREEN
    activate_led(LED_GREEN);
}

void loop() {
    // El código dentro de esta parte se ejecutará
    // mientras el Timer1 genera interrupciones.
}

// Rutina de servicio de interrupción del Timer1
ISR(TIMER1_COMPA_vect) {
     // Cambio de Tiempo al pulsar SW
    if (digitalRead(SW3)==LOW){
        Time200ms();
    } else if (digitalRead(SW4)==LOW){
        Time750ms();
    } else if ((digitalRead(SW3)==LOW)&& digitalRead(SW4)==LOW){// Prioridad al Timer de 200 ms
        Time200ms();
    }

    activate_led(leds[current_led_index-1].pin); // Encender el siguiente LED

    current_led_index += direction_forward;
    if (current_led_index > 4) {
    current_led_index = 1;
    } else if (current_led_index == 0) {
    current_led_index = 4;
    }
}

// Función para encender un LED y apagar los demás
void activate_led(uint8_t pin) {
    for (int i = 0; i < sizeof(leds) / sizeof(leds[0]); ++i) {
        digitalWrite(leds[i].pin, (leds[i].pin == pin) ? HIGH : LOW);
    }
}

// Rutina de interrupción para cambiar la dirección de la secuencia
void cambiodireccion() {
    direction_forward *= -1; // Cambiar dirección signo -
}

// Rutina de interrupción para resetear la dirección de la secuencia
void resetdireccion() {
    direction_forward = 1; // Dirección inicial el signo +
}

// Cambio de Tiempo a 200 ms
void Time200ms() {
    *OCR1A_Ptr = 3124; // (200 ms) (~3125)
}

// Cambio de Tiempo a 750 ms
void Time750ms() {
    *OCR1A_Ptr = 11718; // (750 ms)(~11719)
}
