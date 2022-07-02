void setup() {
  pinMode(28, INPUT);
  pinMode(23, OUTPUT);
  pinMode(27, OUTPUT);

}

void loop() {
  if (digitalRead(28)==1){
    digitalWrite(23, HIGH);
    }
  }

void led_function() {
  digitalWrite(23, HIGH);
}
/*ACTIVE LOGIC, I = OFF, O = ON !!!

if (digitalRead(52)==1)
  {
    led_function();
  }
  else 
  {
    digitalWrite(9, LOW);
  }
}
*/
