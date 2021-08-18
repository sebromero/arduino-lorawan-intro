#include <Arduino_MKRENV.h>

#define PRESSURE_READINGS_COUNT 20 // The amount of samples to take
#define PRESSURE_READ_INTERVAL 3 * 60 * 60 * 1000 / PRESSURE_READINGS_COUNT // How often to check in 3 hours

unsigned long lastSensorCheck = 0; // To keep track when was the last time to check
float pressureReadings[PRESSURE_READINGS_COUNT] = {};
int pressureReadingIndex = -1;

float temperature;
float humidity;
float pressure;
float illuminance;
float pressureTendency;

/**
 * Simply calculates the moving difference of the numbers in the array
 * and returns a positive or negative number indicating the trend.
 * It reads the ring buffer in two steps. First the values up to the current
 * index, then the values from the previous fill.
 * */
template <size_t N>
float calculatePressureTrend(float (&readings)[N], int currentIndex){
  float trend = 0;  
  auto arraySize = N;
  
  // Loop over the newest values
  for(int i = 0; i < currentIndex; ++i){
    auto currentValue = pressureReadings[i];
    auto nextValue = pressureReadings[i+1];
    // Skip if no readings are available
    if(isnan(currentValue) || isnan(nextValue)) break;
    auto difference = nextValue - currentValue;
    trend += difference;
  }

  // Loop over the previous values
  for (int i = currentIndex + 1; i < arraySize - 1; ++i) {
    auto currentValue = pressureReadings[i];
    auto nextValue = pressureReadings[i+1];
    // Skip if no readings are available
    if(isnan(currentValue) || isnan(nextValue)) break;
    auto difference = nextValue - currentValue;    
    trend += difference;
  }
  
  return trend;
}

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // Pre-populate the array with NAN values so that we can
  // determine which are invalid values when reading the buffer.
  auto amountOfReadings = sizeof(pressureReadings) / sizeof(float);
  for (size_t i = 0; i < amountOfReadings; i++){
    pressureReadings[i] = NAN;
  }

  if (!ENV.begin()) {
    Serial.println("Failed to initialize MKR ENV shield!");
    while (1);
  }
}

void maybeUpdatePressureTendency(float sensorValue){
  // Determine if it's time to update the sensor reading
  if(millis() - lastSensorCheck < PRESSURE_READ_INTERVAL) return;

  pressureReadingIndex = (pressureReadingIndex + 1) % PRESSURE_READINGS_COUNT;
  pressureReadings[pressureReadingIndex] = sensorValue;
  Serial.print("Updating sensor value at index: ");
  Serial.println(pressureReadingIndex);
  lastSensorCheck = millis();
}

void loop() {
  // read all the sensor values
  temperature = ENV.readTemperature();
  humidity    = ENV.readHumidity();
  pressure    = ENV.readPressure();
  illuminance = ENV.readIlluminance();
  maybeUpdatePressureTendency(pressure);
  pressureTendency = calculatePressureTrend(pressureReadings, pressureReadingIndex);

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

  Serial.print("Pressure Tendency = ");  
  Serial.print(pressureTendency);
  Serial.println(" kPa");  

  // print an empty line
  Serial.println();

  // TODO: Send values to LoRaWAN network
  /* Keep the following order of variables when constructing the packet:
  1. temperature
  2. humidity
  3. pressure
  4. illuminance
  5. pressureTendency
  */

  // wait 120 seconds to send again
  delay(120000);
}
