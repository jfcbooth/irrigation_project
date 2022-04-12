// Includes
#include <SD.h> // Sd card
#include <DFRobot_DHT20.h> // Humidity / Moisture sensor

// Input
#define MOIST 17
#define VOLTAGE_READER 2

// Output
#define DHT_SWITCH
#define H2O_SWITCH 16
#define WATER 15
#define LED 14
#define SD_PIN 6

// Global Variables
File readLog;
char junk;
String inputString = "";
long moistIdeal;
int soilType;
DFRobot_DHT20 dht20;

void setup() {
  Serial.begin(9600);
  dht20.begin();
  
  // Input
  pinMode(MOIST, INPUT);
  pinMode(VOLTAGE_READER, INPUT);

  // Output
  pinMode(DHT_SWITCH, OUTPUT);
  pinMode(H2O_SWITCH, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(SD_PIN, OUTPUT);

  // Setup
  moistIdeal = 0;
}

void loop() {
  long moistCurrent;
  long humid;
  long temp;

  while(!SD.begin(SD_PIN)) {
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
  }

  readLog = SD.open("log.txt", FILE_WRITE);
  moistCurrent = analogRead(MOIST);
  humid = dht20.getHumidity();
  temp = dht20.getTemperature();

  if (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;
  }
}
