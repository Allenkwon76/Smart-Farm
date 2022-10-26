int cds;
int led = 6;

void setup() {
  Serial.begin(9600);
  pinMode(6, OUTPUT);
}

void loop() {
  cds = analogRead(A0);
  Serial.println(cds);
  delay(500);

  if(cds > 50){
    digitalWrite(led, HIGH);
    }
  else{
    digitalWrite(led, LOW);
    }
}
