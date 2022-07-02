#include <AFMotor.h>
AF_DCMotor motor1 (1);

void setup() {
  motor1.setSpeed(150);
  //motor1.run(RELEASE);
  Serial.begin(9600);
}

void loop() {
  //int i;
  motor1.run(FORWARD);
  /*for (i = 0; i <= 255; i++){   
    Serial.print("Current Motor Speed: ");
    Serial.println(i);
    motor1.setSpeed(i);
    delay(500);*/
  }
  //motor1.run(FORWARD);
  //delay(5000);
  //motor1.run(RELEASE);
  //delay(5000);
  //motor1.run(BACKWARD);
  //delay(2000);
