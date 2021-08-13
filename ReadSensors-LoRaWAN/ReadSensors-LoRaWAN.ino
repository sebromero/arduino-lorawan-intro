/*
  MKR ENV Shield - Read Sensors

  This example reads the sensors on-board the MKR ENV shield
  and prints them to the Serial Monitor once a second.

  The circuit:
  - Arduino MKR board
  - Arduino MKR ENV Shield attached

  This example code is in the public domain.
*/

#include <MKRWAN.h>
#include <Arduino_MKRENV.h>
#include "arduino_secrets.h"

LoRaModem modem;

float temperature;
float humidity;
float pressure;
float illuminance;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!ENV.begin()) {
    Serial.println("Failed to initialize MKR ENV shield!");
    while (1);
  }  

  // change this to your regional band (eg. US915, AS923, ...)
  if (!modem.begin(EU868)) {
    Serial.println("Failed to start module");
    while (1) {}
  };

  connectToLoRaWAN();
}

void connectToLoRaWAN(){
  Serial.println("Connecting...");
  int connected = modem.joinOTAA(APP_EUI, APP_KEY);

  if (!connected) {
    Serial.println("Something went wrong; are you indoor? Move near a window and retry");
    while (1) {}
  }

  delay(5000);
}

void sendSensorValues(){
  Serial.println("Sending message...");
  modem.setPort(3);
  modem.beginPacket();
  modem.write<float>(temperature);
  modem.write<float>(humidity);
  modem.write<float>(pressure);
  modem.write<float>(illuminance);
    
  int error = modem.endPacket(true);
  
  if (error > 0) {
    Serial.println("Message sent correctly!");
  } else {
    Serial.println("Error sending message :(");
  }
  
  Serial.println();
}

void loop() {
  // read all the sensor values
  temperature = ENV.readTemperature();
  humidity    = ENV.readHumidity();
  pressure    = ENV.readPressure();
  illuminance = ENV.readIlluminance();

  // print each of the sensor values
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity    = ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Pressure    = ");
  Serial.print(pressure);
  Serial.println(" kPa");

  Serial.print("Illuminance = ");
  Serial.print(illuminance);
  Serial.println(" lx");

  // print an empty line
  Serial.println();

  sendSensorValues();

  // wait 120 seconds to print again
  delay(120000);
}
