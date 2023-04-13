#include <Servo.h>

#include "common.h"

RF24 radio_gugu(9, 10);
int data[5];

struct ServAngle {
  Servo servo;
  int angle = 0;

  auto write() -> decltype(servo.write(angle)) {
    return servo.write(angle);
  }
} serv;

constexpr int servoPin = 2;

void setup() {
  Serial.begin(9600);

  setup_radio(radio_gugu);
  radio_gugu.openReadingPipe(1, pipeAddr);
  radio_gugu.startListening();

  // motor pins
  for (int i = 4; i < 8; ++i) {
    pinMode(i, OUTPUT);
  }

  Serial.println("RADIO GUGU START");

  serv.servo.attach(servoPin);
}
constexpr int SPEED_1 = 5;
constexpr int DIR_1 = 4;
constexpr int SPEED_2 = 6;
constexpr int DIR_2 = 7;


void loop() {
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
      setEngine(HIGH, LOW, spd);
      break;
    case Dir::BACKWARD:
      setEngine(HIGH, LOW, spd);
      break;
    case Dir::RIGHT:
      setEngine(LOW, LOW, spd);
      break;
    case Dir::LEFT:
      setEngine(HIGH, HIGH, spd);
      break;
    default:
      setEngine(HIGH, HIGH, 0);
      Serial.println("No direction");
  }
}
