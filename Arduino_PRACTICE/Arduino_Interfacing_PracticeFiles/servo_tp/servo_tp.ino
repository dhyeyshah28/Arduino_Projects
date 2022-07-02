#include <Servo.h>
Servo servo;
int ang = 0;
void setup() {
  servo.attach(8);
  servo.write(90);
}

void loop() {
  for (ang=0; ang<180; ang ++){
    servo.write(ang);
    delay(10);
  }
  ///for (ang=180; ang<1; ang --){
    ///servo.write(ang);
    ///delay(10);
  

}
