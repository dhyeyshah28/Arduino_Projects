int a = 13;
int time;

void setup() {
  // put your setup code here, to run once:
  pinMode (a, OUTPUT);
  pinMode (6, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(6) == LOW)
    {digitalWrite(5, HIGH);
    Serial.print(" I detect an Object ");
    delay(100);
    Serial.print(" Time: "); time = millis();
    Serial.println(time);
    if (time % 2 == 0)
      {Serial.print(" This is Even Time ");
      }
    }
    
  else
    {digitalWrite(5, LOW);
    Serial.print(" NO obstacle detected ");
    delay(100);
    }
  
}
