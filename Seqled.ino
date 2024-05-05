#define LED_GREEN 7
#define LED_YELLOW 6
#define LED_RED 5
#define LED_BLUE 4
#define SW1 2
#define SW2 3
#define SW3 11
#define SW4 12

volatile int indiceLED = 0; // Variable que guarda el índice del LED actual
volatile int direction = 1; // Variable que indica la dirección de la secuencia
volatile bool val = true;

void setup() {
  Serial.begin(9600);
  Serial.print("Secuencia inicial: ");
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
  
  // Inicialmente, todos los LEDs están apagados
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_BLUE, LOW);
  
  // Configurar el TIMER1. Nota: (Timer0: 8bits) - (Timer1: 16bits)
  // OCR1A = (fosc*Ts)/(prescaler) < 65536, fosc = 16 MHz
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 3124; // Iniciamos a 200 ms
  TCCR1A |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (0 << CS11) | (1 << CS10); // prescaler: 1024
  TIMSK1 |= (1 << OCIE1A); // habilita comparacion A
  
  sei();  // Permite las interrupciones
}

void loop(){
}

// Rutina de interrupción para el Timer1
ISR(TIMER1_COMPA_vect) {
  // Cambio de Tiempo al pulsar SW
  if (digitalRead(SW3)==LOW){
    Time200ms();
  } else if (digitalRead(SW4)==LOW){
    Time750ms();
  } else if ((digitalRead(SW3)==LOW)&& digitalRead(SW4)==LOW){// Prioridad al Timer de 200 ms
    Time200ms();
  }
  // Secuencia inicial apagados Todos
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_BLUE, LOW);
    
  // Encender el LED correspondiente según la secuencia y la dirección
  switch(indiceLED) {
    case 0:
    digitalWrite(LED_GREEN, HIGH);
    Serial.print("GREEN-");
    break;
    case 1:
    digitalWrite(LED_YELLOW, HIGH);
    Serial.print("YELLOW-");
    break;
    case 2:
    digitalWrite(LED_RED, HIGH);
    Serial.print("RED-");
    break;
    case 3:
    digitalWrite(LED_BLUE, HIGH);
    Serial.print("BLUE-");
    break;
  }
  
  // Incrementar (+1) o decrementar (-1) apartir de la direccion de la secuencia
  indiceLED += direction;
  if (indiceLED > 3) {
    indiceLED = 0;
  } else if (indiceLED < 0) {
    indiceLED = 3;
  }
  
}

// Rutina de interrupción para cambiar la dirección de la secuencia
void cambiodireccion() {
  Serial.println("");Serial.print("Cambio de direccion: ");
  direction *= -1; // Cambiar dirección signo -
}

// Rutina de interrupción para resetear la dirección de la secuencia
void resetdireccion() {
  Serial.println("");Serial.print("Restaura direccion: ");
  direction = 1; // Dirección inicial el signo +
}

// Cambio de Tiempo a 200 ms
void Time200ms() {
  Serial.println("");Serial.print("Tiempo 200 ms: ");
  OCR1A = 3124; // (200 ms) (~3125)
}

// Cambio de Tiempo a 750 ms
void Time750ms() {
  Serial.println("");Serial.print("Tiempo 750 ms: ");
  OCR1A = 11718; // (750 ms)(~11719)
}