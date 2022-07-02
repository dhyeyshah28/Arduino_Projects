#include <Servo.h>

const int tp = 12;
const int ep = 13;
int dist;
int dur;
int ang = 0;
Servo motor;

void setup() {
  pinMode(tp, OUTPUT);
  pinMode(ep, INPUT);
  motor.attach(8);
  motor.write(0);
  Serial.begin(9600);

}

void loop() {
  digitalWrite(tp, HIGH);
  delay(250);
  digitalWrite(tp, LOW);

  dur = pulseIn(ep, HIGH);
  
  dist = (dur/2)/29.1;

  if (dist<15) {
    Serial.println("Hii");
    ///Serial.println(dist);
    motor.write(170);
    delay(10000);
    motor.write(0);
  }
  else {
    Serial.println(dist);
  
  }
}
