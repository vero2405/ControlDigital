const int16_t LED_GREEN = 7;
const int16_t LED_YELLOW = 6;
const int16_t LED_RED = 5;
const int16_t LED_BLUE = 4;
const int16_t SW1 = 2;
const int16_t SW2 = 3;
const int16_t SW3 = 11;
const int16_t SW4 = 12;


int16_t leds[] = {LED_GREEN, LED_YELLOW, LED_RED, LED_BLUE};
int16_t len = sizeof(leds)/sizeof(int16_t);
enum dir {ascending, descending};
typedef struct{
  int16_t* leds;
  int16_t len;
  dir orientation;
} control_leds;

void turnOffLeds(control_Leds cleds);
dir readKey(int16_t key);
void ledSequence(int16_t* leds, int16_t len, dir orientation);

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
