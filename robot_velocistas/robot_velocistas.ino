


//EXPANSOR I2C PCF8574
int a;
#include <Adafruit_NeoPixel.h>
#define SDA_PORT PORTD
#define SDA_PIN 4
#define SCL_PORT PORTD
#define SCL_PIN 5
#include <SoftWire.h>
SoftWire EXP = SoftWire();
const int expAddress = 0x20; //0x20 para PCF8574P; 0x38 para PCF8574AP
unsigned char expOutputRegister = 0b11111111;
void set_exp_value(char pin, char value);
byte get_exp_value(char pin);
#define EXP_P0 0
#define EXP_P1 1
#define EXP_P2 2
#define EXP_P3 3
#define EXP_P4 4
#define EXP_P5 5
#define EXP_P6 6
#define EXP_P7 7
Adafruit_NeoPixel neopixel = Adafruit_NeoPixel(2, 2, NEO_GRB + NEO_KHZ800);
// LEDS
#define LED_R EXP_P1
#define MOTOR_IZQ_1 EXP_P2
#define MOTOR_IZQ_2 EXP_P3
#define MOTOR_DER_1 EXP_P4
#define MOTOR_DER_2 EXP_P5
#define SET_LED_R_HIGH set_exp_value(LED_R, HIGH)
#define SET_LED_R_LOW set_exp_value(LED_R, LOW)
#define LED_G EXP_P0
#define SET_LED_G_HIGH set_exp_value(LED_G, HIGH)
#define SET_LED_G_LOW set_exp_value(LED_G, LOW)
#define GET_BUTTON_1 get_exp_value(6)
#define GET_BUTTON_2 get_exp_value(7)
#define SET_MOTOR_IZQ_1_HIGH set_exp_value(MOTOR_IZQ_1, HIGH)
#define SET_MOTOR_IZQ_1_LOW set_exp_value(MOTOR_IZQ_1, LOW)
#define SET_MOTOR_IZQ_2_HIGH set_exp_value(MOTOR_IZQ_1, HIGH)
#define SET_MOTOR_IZQ_2_LOW set_exp_value(MOTOR_IZQ_1, LOW)
#define SET_MOTOR_DER_1_HIGH set_exp_value(MOTOR_DER_1, HIGH)
#define SET_MOTOR_DER_1_LOW set_exp_value(MOTOR_DER_1, LOW)
#define SET_MOTOR_DER_2_HIGH set_exp_value(MOTOR_DER_1, HIGH)
#define SET_MOTOR_DER_2_LOW set_exp_value(MOTOR_DER_1, LOW)


void setup() {
  Serial.begin(9600);
  neopixel.begin();
  pinMode(6, OUTPUT);
}

void loop() {
  // MOTOR IZQUIERDA
    set_exp_value(MOTOR_IZQ_1, LOW);
    set_exp_value(MOTOR_IZQ_2, HIGH);
    analogWrite(6, 255);
  // MOTOR DERECHA
    set_exp_value(MOTOR_DER_1, HIGH);
    set_exp_value(MOTOR_DER_2, LOW);
    analogWrite(3, 255);
  // LEDS
    red_led(GET_BUTTON_1);
    blue_led(GET_BUTTON_2);
for(int a = 0; a < 255; a++){
     neopixel.setPixelColor(0, a, 255, random(0,255));
    neopixel.show();
}
for(int a = 255; a > 0; a--){
    neopixel.setPixelColor(1, a, 255, 255);
    neopixel.show();
}
}

void set_exp_value(char pin, char value) {
  if (value == HIGH)
    expOutputRegister = expOutputRegister & (~(1 << pin));
  else // value == LOW
    expOutputRegister = expOutputRegister | (1 << pin);

  EXP.beginTransmission(expAddress);
  EXP.write(expOutputRegister);
  EXP.endTransmission();
}

byte get_exp_value(char pin) {
  byte value = 0;

  EXP.requestFrom(expAddress, 1);
  if (EXP.available())
    value = EXP.read();
  EXP.endTransmission();

  return (value & 1 << pin) >> pin;
}
void red_led (byte a) {
  a = GET_BUTTON_1;
  if (a == LOW) SET_LED_R_HIGH;
  else SET_LED_R_LOW;
}
void blue_led (byte b) {
  b = GET_BUTTON_2;
  if (b == LOW) SET_LED_G_HIGH;
  else SET_LED_G_LOW;
}

