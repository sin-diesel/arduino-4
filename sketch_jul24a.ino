
void setup() {
  // put your setup code here, to run once:
  for (int i = 4; i < 8; i++) {     
    pinMode(i, OUTPUT);
  }
}
constexpr int SPEED_1 = 5;
constexpr int DIR_1 = 4;
constexpr int SPEED_2 = 6;
constexpr int DIR_2 = 7;


void loop() {
  // устанавливаем направление мотора «M1» в одну сторону
  digitalWrite(DIR_1, LOW);
  // включаем мотор на максимальной скорости
  analogWrite(SPEED_1, 255);
  // ждём одну секунду
  delay(1000);
  // устанавливаем направление мотора «M1» в другую сторону
  digitalWrite(DIR_1, HIGH);
  // ждём одну секунду
  delay(1000);
  // выключаем первый мотор
  analogWrite(SPEED_1, 0);
  // устанавливаем направление мотора «M2» в одну сторону
  digitalWrite(DIR_2, LOW);
  // включаем второй мотор на максимальной скорости
  analogWrite(SPEED_2, 255);
  // ждём одну секунду
  delay(1000);   
  // устанавливаем направление мотора «M2» в другую сторону
  digitalWrite(DIR_2, HIGH);
  // ждём одну секунду
  delay(1000);
  // выключаем второй мотор
  analogWrite(SPEED_2, 0);
  // ждём одну секунду
  delay(1000);
 }
