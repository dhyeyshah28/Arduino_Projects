char val;
void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  //pinMode(8, OUTPUT);
  pinMode(26, OUTPUT);
  //digitalWrite(8, HIGH);
  digitalWrite(23, HIGH);
}

void loop() {
  if (Serial1.available()>0)
  {
    val = Serial1.read();
    Serial.println(val);
  }
  
  if (val == '1')
  {
    //digitalWrite(8, HIGH);
    digitalWrite(26, HIGH);
    }
  else if (val == '0')
  {
    //digitalWrite(8, LOW);
    digitalWrite(26, LOW);
    
    }

}
