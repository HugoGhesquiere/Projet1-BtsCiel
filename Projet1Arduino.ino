#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <FanController.h>
#include <Wire.h>
#include <DHT.h> // Inclure la bibliothèque DHT
#include <Ethernet.h>
#include <SPI.h>

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

// setup les autres addresse ip
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED } // Adresse MAC Shield ethernet
IPAddress ip(172, 16, 35, 166);
IPAddress pcIp(172, 18, 3, 165); //a modif
IPAddress mySubnet(255, 255, 0, 0); // Masque de sous-réseau
IPAddress myGateway(192, 168, 1, 1); // Adresse IP de la passerelle (routeur)//a changer)

// Initialiser une instance Ethernet  
EthernetServer server(80); // Création d'un serveur sur le port 80

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.init();   // initialisation du LCD
  lcd.backlight();   // active le rétroéclairage lcd.noBacklight() pour le désactiver
  lcd.clear();

   Ethernet.begin(mac, ip, myGateway, mySubnet);
   
   server.begin();
   // test pour serveur ethernet
   Serial.print("Serveur prêt à l'adresse : ");
   Serial.println(Ethernet.localIP());

    // Restez à l'écoute des clients  
    EthernetClient client = server.available();
    if (client) {
        // Traitez le client ici  
        // ...
        client.stop(); // Ferme la connexion  
    }
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
