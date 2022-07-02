#include <NewPing.h>
#define TRIGGER_PIN A9
#define ECHO_PIN A8
#define MAX_DISTANCE 300

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  Serial.begin(9600);
  
}

void loop() {
  int distance = sonar.ping_cm();
  delay(1000);
  Serial.println(distance);

}
