#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <FanController.h>
#include <Wire.h>
#include <DHT.h> // Inclure la bibliothèque DHT

// Définir l'adresse de l'écran LCD  
#define LCD_ADDRESS 0x27 // Remplacez ceci par l'adresse correcte de votre écran LCD  
#define LCD_ROWS 2  
#define LCD_COLUMNS 16  
#define SCROLL_DELAY 150  
#define BACKLIGHT 255  

#define FAN_PIN 5

#define DHT_PIN 4 // Remplacez par le numéro de broche utilisé pour le capteur DHT  
#define DHT_TYPE DHT22 // Type de capteur (DHT11 ou DHT22) pour AM2302

DHT dht(DHT_PIN, DHT_TYPE); // Créer une instance du capteur DHT

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.init();   // initialisation du LCD
  lcd.backlight();   // active le rétroéclairage lcd.noBacklight() pour le désactiver
  lcd.clear();
}


void loop() {
  float Temperature = dht.readTemperature(); // Lire la température à partir du capteur DHT  
  float Humidity = dht.readHumidity(); // Lire l'humidité à partir du capteur DHT
  
  if (isnan(Temperature) || isnan(Humidity)) {
    Serial.println("Échec de la lecture du capteur DHT !");
    lcd.clear(); // Effacer l'écran LCD  
    lcd.print("Erreur capteur"); // Afficher un message d'erreur  
  }
  
  // Logique du ventilateur  
  if (Temperature > 26.0) {
    digitalWrite(FAN_PIN, HIGH);
    Serial.println("Température Trop élevée");
  } 
  else if (Temperature < 20.0) {
    Serial.println("Température Trop Basse");
    digitalWrite(FAN_PIN, LOW);
  } 
  
  if (Humidity > 60) {
    Serial.println("Humidité Trop Haute"); // À afficher dans le site  
  } 
  else if (Humidity < 40) {
    Serial.println("Humidité Trop Basse"); // À afficher dans le site  
    }
  
  // Affichage sur l'écran LCD  
  lcd.clear();  // Déplacer cette ligne ici pour éviter que l'affichage soit trop rapide
  lcd.setCursor(0, 0);
  lcd.print("Humidity:");
  lcd.print(Humidity); 
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("Temp:");
  lcd.print(Temperature);
  lcd.print("C");
    
    
  delay(5000); // Ajouter un délai pour éviter des lectures trop fréquentes  
}
