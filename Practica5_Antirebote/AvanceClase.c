// cambio de estado activa para cambiar de estado (buttonUP a BUTTON falling)
// para delay usar un callback buscar libreria

#define SW1 7

typedef enum {
    ESTADO_INICIAL,
    ESTADO_UP,
    ESTADO_FALLING,
    ESTADO_DOWN,
    ESTADO_RISING
} estado_t;

estado_t estadoActual;

void inicializarMEF(){
    estadoActual = ESTADO_INICIAL;

}

void actualizarMEF(){
    int val = digitalRead(SW1);
  static int prevVal = val;
  bool cambio = val ^ prevVal;  // (^: XOR)

    switch (estadoActual)
    {
    case ESTADO_INICIAL:
        // Inicializar Hardware
        Serial.println("estado Inicial");
        pinMode(SW1,INPUT_PULLUP);
        estadoActual = ESTADO_UP;  // Condicion de cambio (de momento)
        break;
    case ESTADO_UP:
        Serial.println("estado UP");
        estadoActual = ESTADO_FALLING;
        break;
    case ESTADO_FALLING:
        Serial.println("estado FALLING");
        //TIMER 40 MS
        if(){
            estadoActual = ESTADO_UP;
        }
        else{
            estadoActual = ESTADO_DOWN;
        }
        break;
    case ESTADO_DOWN:
        Serial.println("estado DOWN");
        estadoActual = ESTADO_RISING;
        break;
    case ESTADO_RISING:
        Serial.println("estado FALLING");
        //TIMER 40 MS
        if(){
            estadoActual = ESTADO_UP;
        }
        else{
            estadoActual = ESTADO_DOWN;
        }
        break;
    default:
        inicializarMEF();
        break;
    }
    delay(100); // solo por el momento. Esto no se deberia de usar
    prevVal = val;
}

void setup(){
    inicializarMEF();
    Serial.begin(11500);
}
void loop(){
    actualizarMEF();
}

volatile uint16_t previousMillis = 0;  // Variable para almacenar el tiempo anterior
volatile uint16_t currentMillis = millis();  // Obtener el tiempo actual en milisegundos

void DetectorDurante40ms(){
    if (currentMillis - previousMillis >= 40) {
        previousMillis = currentMillis;  // Actualizar el tiempo anterior
        // estado del pin
        }
    // activamos el flag

    }
}