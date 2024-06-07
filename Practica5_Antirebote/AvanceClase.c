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
        // SW
        break;
    case ESTADO_UP:
        
        break;
    case ESTADO_DOWN:
        
        break;
    default:
        inicializarMEF();
        break;
    }
}

