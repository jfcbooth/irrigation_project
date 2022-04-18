// Includes
#include <SD.h> // Sd card
#include <DFRobot_DHT20.h> // Humidity / Moisture sensor
#include <SoftwareSerial.h> // Bluetooth module

// Input
#define MOIST 17 // Input for data from moisture sensor
#define VOLTAGE_READER 2 // Input for reading voltage
#define SD_READ 6 // Used to read data from SD card

// Output
#define DHT_SWITCH  // idk, need to figure this out
#define H2O_SWITCH 16 // Used to complete circuit for moisture sensor
#define WATER 15 // Turns on and off solenoid
#define LED 14 // LED line, self explanitory
#define SD_WRITE 7 // Transmits to SD card

// Global Variables
File readLog; // Variable to refer to file on SD card
long moistIdeal; // Global variable for what our ideal moisture is
DFRobot_DHT20 dht20; // Object for humid/temp sensor
SoftwareSerial Bluetooth(7, 6); // Object for bluetooth module

void setup() {
  // Start up everything
  Bluetooth.begin(9600);
  Serial.begin(9600);
  dht20.begin();
  
  // Set up inputs
  pinMode(MOIST, INPUT);
  pinMode(VOLTAGE_READER, INPUT);
  pinMode(SD_READ, INPUT);

  // Set up outputs
  pinMode(DHT_SWITCH, OUTPUT);
  pinMode(H2O_SWITCH, OUTPUT);
  pinMode(WATER, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(SD_WRITE, OUTPUT);

  // Set any variables
  moistIdeal = 0;
}

void loop() {
  long moist; // Holds read moisture level
  long humid; // Holds read humidity level
  long temp; // Holds read temperature
  // Assume app will have a value set to 0, when data is requested value is set to 1
  // when app starts recieving data it will set the value back to 0

  while(!SD.begin(SD_WRITE)) {
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
  }
  readLog = SD.open("log.txt", FILE_WRITE);

  // Write to app if connected
  if (Bluetooth.available()) {
    Bluetooth.print((char)readLog.read());
  }

  // Read moisture, humidity, temperature
  moist = analogRead(MOIST);
  humid = dht20.getHumidity();
  temp = dht20.getTemperature();

  if (moist < moistIdeal) {
    digitalWrite(WATER, HIGH); // Turn on solenoid
    for (int i = 0; i < 3; i++) { // Water for 15 seconds, checking if app needs updated every 5 seconds
      dataRequested(File readLog);
      delay(5000);
    }
    digitalWrite(WATER, LOW); // Turn off solenoid
  }

  dataRequested(File readLog);
}

void dataRequested(File readLog) {
  int btRequest; // 0 = no, 1 = yes
  btRequest = Bluetooth.read();
  if (btRequest == 1) {
    Bluetooth.print((char)readLog.read());
  }
}
