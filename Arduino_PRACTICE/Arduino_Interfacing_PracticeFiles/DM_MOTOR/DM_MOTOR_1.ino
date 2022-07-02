#include <AFMotor.h>
#include <LiquidCrystal.h>
AF_DCMotor motor1 (2);
LiquidCrystal lcd(12,11,5,4,3,2);

void setup() {
  analogWrite(6,100);
  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);
  lcd.begin(16,2);
  lcd.clear(); 
  motor1.setSpeed(150);
  motor1.run(RELEASE);
  Serial.begin(9600);
}

void loop() {
  int i;
  motor1.run(FORWARD);
  for (i = 0; i <= 255; i++){   
    Serial.print("Current Motor Speed: ");
    Serial.println(i);
    motor1.setSpeed(i);
    delay(500);

    lcd.setCursor(0,0);
    lcd.print("Current Motor Speed:");
    lcd.setCursor(0,1);
    lcd.print(i);
  }
  //motor1.run(FORWARD);
  //delay(5000);
  //motor1.run(RELEASE);
  //delay(5000);
  //motor1.run(BACKWARD);
  //delay(2000);
}
