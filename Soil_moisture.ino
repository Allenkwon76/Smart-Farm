int soil_moisture;

void setup() {
  Serial.begin(9600);
}

void loop() {
  soil_moisture = analogRead(A0);
  Serial.println(soil_moisture);
  delay(500);

  if(soil_moisture <= 450){
    Serial.println("Wet!!");
    }
  if(soil_moisture > 500 && soil_moisture <= 1000){
      Serial.println("Good!!");
      }
    else if(soil_moisture > 1000){
      Serial.println("Dry!!");
      }
}
