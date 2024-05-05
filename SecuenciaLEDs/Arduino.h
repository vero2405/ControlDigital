#ifndef Arduino_h
#define Arduino_h

#include <stdint.h>
#include <stdbool.h>

// Definiciones para el temporizador Timer1
volatile uint8_t *TCCR1A_Ptr = (uint8_t *)0x80;
volatile uint8_t *TCCR1B_Ptr = (uint8_t *)0x81;
volatile uint16_t *TCNT1_Ptr = (uint16_t *)0x84;
volatile uint16_t *OCR1A_Ptr = (uint16_t *)0x88;
volatile uint8_t *TIMSK1_Ptr = (uint8_t *)0x6F;

// Definiciones de bits relevantes para Timer1
#define CS10    0
#define CS11    1
#define CS12    2
#define WGM12   3
#define OCIE1A  1

#ifdef __cplusplus
extern "C" {
#endif

// Definición de constantes para especificar los modos de interrupción
#define LOW     0
#define HIGH    1
#define CHANGE  2
#define RISING  3
#define FALLING 4

// Definiciones de pines y constantes
#define INPUT             0x0
#define OUTPUT            0x1
#define INPUT_PULLUP      0x2
#define HIGH              0x1
#define LOW               0x0

// Funciones de tiempo
unsigned long millis();
unsigned long micros();
void delay(unsigned long);
void delayMicroseconds(unsigned int);

// Funciones de manejo de pines
void pinMode(uint8_t, uint8_t);
void digitalWrite(uint8_t, uint8_t);
int digitalRead(uint8_t);

// Funciones de interrupciones
typedef void (*voidFuncPtr)(void);
void attachInterrupt(uint8_t, voidFuncPtr, int);
void detachInterrupt(uint8_t);

#ifdef __cplusplus
}
#endif

#endif
