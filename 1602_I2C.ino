#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  lcd.init();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("Hello, World");
  lcd.setCursor(4,1);
  lcd.print("Arduino!");
}

void loop() {

}
