#include "Arduino.h"
#include "LiquidCrystal_PCF8574.h"
#include "Fan.h"
#include "Wire.h"
#include "Adafruit_Sensor.h"
#include "Adafruit_AM2320.h"

#define LCD_ADDRESS 0x3F 
// To find your LCD address go to: http://playground.arduino.cc/Main/I2cScanner and run example.
#define LCD_ROWS 2
#define LCD_COLUMNS 16
#define SCROLL_DELAY 150
#define BACKLIGHT 255

void setup() {
  // put your setup code here, to run once:
  int Fan;
  int Humidity;
  float Temperature;
  Serial.begin(9600);
  // initialize the lcdI2C
  lcdI2C.begin(LCD_COLUMNS, LCD_ROWS, LCD_ADDRESS, BACKLIGHT); 
}


void loop() {
  // put your main code here, to run repeatedly:
 Temperature = am2320.readTemperature();
 Humidity = am2320.readTemperature();
 if Temperature > 26{
    digitalWrite(Fan, HIGH);
    Serial.println("Temperature Trop élevée");   // a déplacer ailleur (Ecran lcdI2C ou autre support)
  }
  else if Temperature < 20{
     Serial.println("Temperature Trop Basse");   // a déplacer ailleur (Ecran lcdI2C ou autre support)
  }
  else{
    digitalWrite(Fan, LOW);
  }

  if humiditee > 60{
    Serial.println("Humiditee Trop Haute");   // a déplacer ailleur (Ecran lcdI2C ou autre support)
  }
  else if humiditee < 40{
    Serial.println("Humiditee Trop Basse");   // a déplacer ailleur (Ecran lcdI2C ou autre support)
  }
  
  lcdI2C.print("Hummiditee: ");
  lcdI2C.print(humidite);
  lcdI2C.setCursor(0, 1);
  lcdI2C.print("Temperature: ");
  lcdI2C.print(Temperature);
}
