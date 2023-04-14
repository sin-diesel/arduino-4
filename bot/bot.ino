#include <Servo.h>
#include "FastLED.h"
#include "common.h"

RF24 radio_gugu(9, 10);
int data[5];
constexpr int NUM_LEDS = 5;
CRGB leds[NUM_LEDS];

struct ServAngle {
  Servo servo;
  int angle = 0;

  auto write() -> decltype(servo.write(angle)) {
    return servo.write(angle);
  }
} serv;

constexpr int servoPin = 2;
constexpr int ledPin = 3;

void setup() {
  Serial.begin(9600);

  setup_radio(radio_gugu);
  radio_gugu.openReadingPipe(1, pipeAddr);
  radio_gugu.startListening();

  // motor pins
  for (int i = 4; i < 8; ++i) {
    pinMode(i, OUTPUT);
  }
  FastLED.addLeds<WS2811, ledPin, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(100);

  Serial.println("RADIO GUGU START");

  serv.servo.attach(servoPin);
}
constexpr int SPEED_1 = 5;
constexpr int DIR_1 = 4;
constexpr int SPEED_2 = 6;
constexpr int DIR_2 = 7;

byte counter = 0;
void loop() {

  for (int i = 0; i < NUM_LEDS; i++ ) {         // от 0 до первой трети
    leds[i] = CHSV(counter + i * 2, 255, 255);  // HSV. Увеличивать HUE (цвет)
    // умножение i уменьшает шаг радуги
  }
  counter++;        // counter меняется от 0 до 255 (тип данных byte)
  FastLED.show();
//  delay(5); 

  if (!radio_gugu.available())
    return;
  radio_gugu.read(&data, sizeof(data));
  Serial.println("RADIO GUGU");
  auto btnState = data[2];
  auto tmblrState = data[3];

  auto ptmrVal = data[4];
  serv.angle = map(ptmrVal, 0, 1023, 0, 180);
  serv.write();
  Serial.println(ptmrVal);

  processDir(data[0], data[1]);
}

void setEngine(int dir1, int dir2, int spd) {
  digitalWrite(DIR_1, dir1);
  analogWrite(SPEED_1, spd);

  digitalWrite(DIR_2, dir2);
  analogWrite(SPEED_2, spd);
}

void processDir(int dir, int spd) {
  switch (dir) {
    case Dir::FORWARD:
      setEn      break;
gine(HIGH, LOW, spd);
    case Dir::BACKWARD:
      setEngine(LOW, HIGH, spd);
      break;
    case Dir::RIGHT:
      setEngine(HIGH, HIGH, spd);
      break;
    case Dir::LEFT:
      setEngine(LOW, LOW, spd);
      break;
    default:
      setEngine(HIGH, HIGH, 0);
      Serial.println("No direction");
  }
}
