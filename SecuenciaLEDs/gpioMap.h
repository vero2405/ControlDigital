#ifndef _GPIOMAP_H
#define _GPIOMAP_H

// Definiciones de pines GPIO
#define GPIO_PIN_0  0
#define GPIO_PIN_1  1
#define GPIO_PIN_2  2
// Continuar con los pines necesarios

// Definiciones de puertos GPIO
#define GPIO_PORT_A  'A'
#define GPIO_PORT_B  'B'
#define GPIO_PORT_C  'C'
// Continuar con los puertos necesarios

// Funciones para manejar los pines GPIO
void gpioDigitalWrite(char port, int pin, int value);
int gpioDigitalRead(char port, int pin);
void gpioPinMode(char port, int pin, int mode);

#endif // _GPIOMAP_H
