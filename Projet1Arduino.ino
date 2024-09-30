#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // put your setup code here, to run once:
  const int fan
  const int humidite
  const float temperature
  lcd.begin(); // Démarre l'afficheur
  lcd.backlight(); // Allume le rétro-éclairage

}

void loop() {
  // put your main code here, to run repeatedly:
  if temperature >= AQQCH{
    digitalWrite(fan, HIGH)
  };
  else{
    digitalWrite(fan, LOW)
  };
  lcd.print("Hummiditee: ");
  lcd.print(humidite);
  lcd.setCursor(0, 1);
  lcd.print("Temperature: ");
  lcd.print(temperature);
}
