#include <Arduino_MKRENV.h>

#define TEMPERATURE_READINGS_COUNT 70 // The amount of samples to take: 10 times a day for 7 days
#define TEMPERATURE_READ_INTERVAL 24 * 7 * 60 * 60 * 1000 / TEMPERATURE_READINGS_COUNT // How often to check in 3 hours

unsigned long lastSensorCheck = 0; // To keep track when was the last time to check
float temperatureReadings[TEMPERATURE_READINGS_COUNT] = {};
int temperatureReadingIndex = -1;

template <size_t N> float getAverage(float (&readings)[N]){
  float sum = 0;

  int i;
  for (i = 0; i < N; ++i) {
    auto currentValue = readings[i];
    if(isnan(currentValue)) break;
    sum += currentValue;
  }
  if(i == 0) return NAN;
  return sum / static_cast<float>(i);
}

void setup() {
  Serial.begin(115200);
  while (!Serial);

  // Pre-populate the array with NAN values so that we can
  // determine which are invalid values when reading the buffer.
  auto amountOfReadings = sizeof(temperatureReadings) / sizeof(float);
  for (size_t i = 0; i < amountOfReadings; i++){
    temperatureReadings[i] = NAN;
  }

  if (!ENV.begin()) {
    Serial.println("Failed to initialize MKR ENV shield!");
    while (1);
  }
}

void maybeUpdateTemperature(float sensorValue){
  // Determine if it's time to update the sensor reading
  if(millis() - lastSensorCheck < TEMPERATURE_READ_INTERVAL) return;

  temperatureReadingIndex = (temperatureReadingIndex + 1) % TEMPERATURE_READINGS_COUNT;
  temperatureReadings[temperatureReadingIndex] = sensorValue;
  Serial.print("Updating sensor value at index: ");
  Serial.println(temperatureReadingIndex);
  lastSensorCheck = millis();
}

void loop() {
  float temperature = ENV.readTemperature();
  maybeUpdateTemperature(temperature);
  float weeklyAverage = getAverage(temperatureReadings);

  // print each of the sensor values
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Weekly average = ");  
  Serial.print(weeklyAverage);
  Serial.println(" °C");  

  // print an empty line
  Serial.println();

  // TODO: Send values to LoRaWAN network

  // wait 120 seconds to print again
  delay(120000);
}
