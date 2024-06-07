// cambio de estado activa para cambiar de estado (buttonUP a BUTTON falling)
// para delay usar un callback buscar libreria
typedef enum {
    ESTADO_INICIAL,
    ESTADO_UP,
    ESTADO_DOWN
} estado_t;

estado_t estadoActual;

void inicializarMEF(){
    estadoActual = ESTADO_INICIAL;

}

void actualizarMEF(){
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
        if (digitalReal(SW1)==0){
            estadoActual = ESTADO_DOWN;
        }
        break;
    case ESTADO_DOWN:
        Serial.println("estado DOWN");
        if (digitalReal(SW1)==1){
            estadoActual = ESTADO_UP;
        }
        break;
    default:
        inicializarMEF();
        break;
    }
    delay(100); // solo por el momento. Esto no se deberia de usar
}

//int main(){
//    inicializarMEF();
//    while(1){
//        actualizarMEF();
//    }
//}

void setup(){
    inicializarMEF();
    Serial.begin(11500);
}
void loop(){
    actualizarMEF();
}