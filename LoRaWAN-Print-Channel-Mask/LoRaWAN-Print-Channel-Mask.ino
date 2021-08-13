#include <MKRWAN.h>

LoRaModem modem;

void setup() {
  int status;

  // Initialize serial port at 9600 bauds
  Serial.begin(9600);
  while (!Serial);

  loraSetup();
  
  Serial.println("--------------------------------");
  Serial.println("- MKR WAN 1310 Channel Masking -");
  Serial.println("--------------------------------");

  // Print default channels configuration
  Serial.print("- Default mask: ");
  Serial.println(modem.getChannelMask());

  // Disable all channels
  Serial.println("- Disabling all channels...");  
  for (unsigned int i = 0; i < 72; i++) {
    modem.disableChannel(i);
  }
  
  // Print current channels configuration
  Serial.print("- Current mask: ");
  Serial.println(modem.getChannelMask());
  
  // Enable AU915-928 channels
  // LoRaWAN® Regional Parameters and TTN specification: channels 8 to 15 plus 65 
  Serial.println("- Enabling channels 8 to 15 plus 65...");  
  for (unsigned int i = 8; i <= 15; i++) {
    modem.enableChannel(i);
  }

  modem.enableChannel(65);

  // Print current channels configuration
  Serial.print("- Current mask: ");
  Serial.println(modem.getChannelMask());
}

void loraSetup() {
  // Initialize LoRa module with the US915-928 region parameters
  if (!modem.begin(US915)) {
    Serial.println("- Failed to start LoRa module!");
    while (1);
  };

  delay(5000);
  
  // Set poll interval to 30 seconds
  modem.minPollInterval(30);
}

void loop() {  
}
