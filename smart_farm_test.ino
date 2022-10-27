/* 스마트 화분 관리기 */
/* 4~5시간? */
/* 들어가는 센서 종류 : 온습도 센서, 조도 센서, 토양 수분 센서, 릴레이 모듈, LCD 모듈, 생장 LED */
/* 필요한 기능
 *  1. 조도 센서를 이용해서 자연광을 측정하고, 자연광의 강도가 낮아지면 생장 LED를 켜서 화분의 식물을 관리한다.
 *  2. 온습도 센서를 이용해서 화분 주변 환경의 온습도를 측정한다.
 *  3. 토양 수분 센서를 이용해 토양의 수분을 측정한다.
 *  4. 릴레이 모듈을 생장 LED와 연결하여 조도 센서값에 따라 생장 LED가 켜질 수 있도록 한다.
 *  5. LCD 모듈을 통해서 온습도 센서와 토양 수분 센서 측정 값을 출력한다.
 */
#include <Wire.h>
#include <LiquidCrystal_I2C.h>      // LCD 모듈 라이브러리
#include <DHT.h>                    // 온습도 센서 모듈 라이브러리
#include <Emotion_Farm.h>           // 특수 문자 및 이모티콘 라이브러리
 
// 센서 핀 설정
#define relayPin 3                  // 릴레이 모듈 핀 -> 생장 LED 켜기 위함
#define cdsPin A1                   // 조도센서 모듈 핀
#define DHTPIN 4                    // 온습도센서 모듈 핀
#define DHTTYPE DHT11               // 온습도 센서타입 설정
#define soilmoisturePin A0          // 토양수분센서 핀

// 객체 생성
LiquidCrystal_I2C lcd(0x27, 16, 2); //LCD 초기화 (LCD 주소값, x축, y축)
DHT dht(DHTPIN, DHTTYPE);           //온습도 센서 모듈

// 문자열을 출력하기 위한 변수
char str_M[10];
char str_T[10];
char str_H[10];

void setup() {
  Serial.begin(9600);

  pinMode(relayPin, OUTPUT);
  pinMode(cdsPin, INPUT);
  pinMode(soilmoisturePin, INPUT);

  //LCD에 인트로 출력
  lcd.begin();
  lcd.clear();
  lcd.noBacklight();
  delay(500);
  lcd.backlight();
  delay(500);
  lcd.setCursor(2,0);
  lcd.print("SMART");
  delay(1000);
  lcd.setCursor(8,0);
  lcd.print("GARDEN");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("BP LAB CodingEdu");
  delay(1000);
  lcd.clear();


  // 라이브러리로 추가한 특수 문자 및 이모티콘 추가
  lcd.createChar(0, temp);
  lcd.createChar(1, C);
  lcd.createChar(2, humi);  
  lcd.createChar(3, Qmark);
  lcd.createChar(4, water);
  lcd.createChar(5, good);
  lcd.createChar(6, wind);
}

void loop() {

  //센서값 측정
  int cdsValue = analogRead(cdsPin);                                 // 조도센서 값 측정: 0(밝음) ~ 1023(어두움)
  int soilmoistureValue = analogRead(soilmoisturePin);               // 토양수분 값 측정: 0(습함) ~ 1023(건조)
  int soilmoisture_per = map(soilmoistureValue, 170, 1023, 100, 0);  // 센서 값을 퍼센트로 변경
  unsigned char h_Value = dht.readHumidity();                        // 공기 중 습도 값 측정
  unsigned char t_Value = dht.readTemperature();                     // 공기 중 온도 값 측정

  //LCD에 토양 습도값 출력
  lcd.setCursor(1,0);
  lcd.print("MOIST:");
  sprintf(str_M, "%03d", soilmoisture_per);
  lcd.print(str_M);
  lcd.setCursor(10,0);
  lcd.print("%");

  //LCD에 온도값 출력
  lcd.setCursor(1,1);
  lcd.write(0);
  sprintf(str_T, "%02d", t_Value);
  lcd.setCursor(3,1);
  lcd.print(str_T);
  lcd.write(1);

  //LCD에 습도값 출력
  lcd.setCursor(7,1);
  lcd.write(2);
  sprintf(str_H, "%02d", h_Value);
  lcd.setCursor(9,1);
  lcd.print(str_H);
  lcd.print("%");

  //조도센서 값에 따른 생장 LED 켜기
  if(cdsValue < 400){
    digitalWrite(relayPin, LOW);
  }
  else if(cdsValue >= 400){
    digitalWrite(relayPin, HIGH);
  }

  //토양습도 값에 따른 LCD에 이모티콘 띄우기
  if(soilmoisture_per >= 0 && soilmoisture_per < 30){
    lcd.setCursor(13,0);
    lcd.write(3);
    lcd.setCursor(14,0);
    lcd.write(4);
  }
  else if(soilmoisture_per >= 30 && soilmoisture_per < 70){
    lcd.setCursor(13,0);
    lcd.print(" ");
    lcd.setCursor(14,0);
    lcd.write(5);
  }
  else if(soilmoisture_per >= 70){
    lcd.setCursor(13,0);
    lcd.write(3);
    lcd.setCursor(14,0);
    lcd.write(6);
  }
  Serial.print(cdsValue);
  Serial.println(soilmoisture_per);
  
  delay(500);
}
