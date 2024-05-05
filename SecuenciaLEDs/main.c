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

typedef struct{
  uint8_t pin;
  bool state;
} control_leds;

control_leds leds[] = {
    {LED_GREEN, false},
    {LED_YELLOW, false},
    {LED_RED, false},
    {LED_BLUE, false}
};

// Puntero a la estructura control_leds
control_leds *LEDactual;

volatile int indiceLED = 0; // Variable que guarda el índice del LED actual
volatile int direction = 1; // Variable que indica la dirección de la secuencia
volatile bool val = true;

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
}

void loop(){
}

// Rutina de interrupción para el Timer1
ISR(TIMER1_COMPA_vect) {

  // Encendemos el led actual
    digitalWrite(LEDactual->pin, HIGH);

}

// Rutina de interrupción para cambiar la dirección de la secuencia
void cambiodireccion() {
  direction *= -1; // Cambiar dirección signo -
}

// Rutina de interrupción para resetear la dirección de la secuencia
void resetdireccion() {
  direction = 1; // Dirección inicial el signo +
}

// Cambio de Tiempo a 200 ms
void Time200ms() {
  *OCR1A_Ptr = 3124; // (200 ms) (~3125)
}

// Cambio de Tiempo a 750 ms
void Time750ms() {
  *OCR1A_Ptr = 11718; // (750 ms)(~11719)
}