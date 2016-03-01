String content = "";

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    content = Serial.readStringUntil('/n'); 
  }

  //delay(5000);
  Serial.print("Arduino: ");
  Serial.println(content);
}
