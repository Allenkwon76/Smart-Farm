void setup() {
  pinMode(8,OUTPUT);     // 8번 핀을 릴레이모듈 출력핀으로 설정
  digitalWrite(8,LOW);   // 릴레이 모듈을 끈다.
}

void loop() {
  digitalWrite(8,HIGH);    // 릴레이 모듈을 킨다.(ON)
  delay(500);             // 시간지연 0.5초
  digitalWrite(8,LOW);    // 릴레이 모듈을 끈다.(NC)
  delay(500);             // 시간지연 0.5초
}
