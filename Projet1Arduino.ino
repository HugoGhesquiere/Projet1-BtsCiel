#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // put your setup code here, to run once:
  const int fan;
  const int humiditee;
  const float temperature;
  Serial.begin(9600);
  lcd.begin(); // Démarre l'afficheur
  lcd.backlight(); // Allume le rétro-éclairage

}

void loop() {
  // put your main code here, to run repeatedly:
  if temperature > 26{
    digitalWrite(fan, HIGH);
    Serial.println("Temperature Trop élevée");   // a déplacer ailleur (Ecran lcd ou autre support)
  }
  else if temperature < 20{
     Serial.println("Temperature Trop Basse");   // a déplacer ailleur (Ecran lcd ou autre support)
  }
  else{
    digitalWrite(fan, LOW);
  }


  if humiditee > 60{
    Serial.println("Humiditee Trop Haute");   // a déplacer ailleur (Ecran lcd ou autre support)
  }
  else if humiditee < 40{
    Serial.println("Humiditee Trop Basse");   // a déplacer ailleur (Ecran lcd ou autre support)
  }
  
  lcd.print("Hummiditee: ");
  lcd.print(humidite);
  lcd.setCursor(0, 1);
  lcd.print("Temperature: ");
  lcd.print(temperature);
}
