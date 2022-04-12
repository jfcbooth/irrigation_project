// Includes
#include <SD.h> // Sd card
#include <SoftwareSerial.h> // Bluetooth module

// Input
#define TEMP
#define HUMID
#define MOIST
#define DIAL_1
#define DIAL_2
#define DIAL_3
#define DIAL_4
#define DIAL_5
#define DIAL_6
#define DIAL_7

// Output
#define DHT_SWITCH
#define H2O_SWITCH
#define LED
#define SD_PIN

// Global Variables
File readLog;
long moistIdeal;

void setup() {
  Serial.begin(9600);
  
  // Input
  pinMode(TEMP, INPUT);
  pinMode(HUMID, INPUT);
  pinMode(MOIST, INPUT);
  pinMode(DIAL_1, INPUT);
  pinMode(DIAL_2, INPUT);
  pinMode(DIAL_3, INPUT);
  pinMode(DIAL_4, INPUT);
  pinMode(DIAL_5, INPUT);
  pinMode(DIAL_6, INPUT);
  pinMode(DIAL_7, INPUT);

  // Output
  pinMode(DHT_SWITCH, OUTPUT);
  pinMode(H2O_SWITCH, OUTPUT);
  pinMode(LED, OUTPUT);

  // Setup
  if (digitalRead(DIAL_1)) {
    moistIdeal = 0;
  } else if(digitalRead(DIAL_2)) {
    moistIdeal = 0;
  } else if(digitalRead(DIAL_3)) {
    moistIdeal = 0;
  } else if(digitalRead(DIAL_4)) {
    moistIdeal = 0;
  } else if(digitalRead(DIAL_5)) {
    moistIdeal = 0;
  } else if(digitalRead(DIAL_6)) {
    moistIdeal = 0;
  } else if(digitalRead(DIAL_7)) {
    moistIdeal = 0;
  }
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
  moistCurrent = digitalRead(MOIST);
  humid = digitalRead(HUMID);
  temp = digitalRead(TEMP);

  if (
}
