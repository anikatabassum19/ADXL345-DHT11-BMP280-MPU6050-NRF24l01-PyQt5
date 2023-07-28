#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);  // Set CE and CSN pins

struct SensorData {
  float temperature;
  float humidity;
  float pressure;
  float altitude;
  float accelerationX;
  float accelerationY;
  float accelerationZ;
  float gyroX;
  float gyroY;
  float gyroZ;
};

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, 0xF0F0F0F0E1LL);  // Set the address for communication
  radio.setPALevel(RF24_PA_HIGH);  // Set the power amplifier level
  radio.startListening();  // Put the module in receiving mode
}

void loop() {
  if (radio.available()) {
    SensorData data;  // Create a structure to hold the received data
    radio.read(&data, sizeof(data));  // Read the received data structure

    Serial.println("----- Received Sensor Data -----");
    Serial.print("Temperature: ");
    Serial.print(data.temperature);
    Serial.println(" °C");
    Serial.print("Humidity: ");
    Serial.print(data.humidity);
    Serial.println(" %");
    Serial.print("Pressure: ");
    Serial.print(data.pressure);
    Serial.println(" hPa");
    Serial.print("Altitude: ");
    Serial.print(data.altitude);
    Serial.println(" meters");
    Serial.print("Acceleration X: ");
    Serial.print(data.accelerationX);
    Serial.println(" m/s^2");
    Serial.print("Acceleration Y: ");
    Serial.print(data.accelerationY);
    Serial.println(" m/s^2");
    Serial.print("Acceleration Z: ");
    Serial.print(data.accelerationZ);
    Serial.println(" m/s^2");
    Serial.print("Gyroscope X: ");
    Serial.print(data.gyroX);
    Serial.println(" °/s");
    Serial.print("Gyroscope Y: ");
    Serial.print(data.gyroY);
    Serial.println(" °/s");
    Serial.print("Gyroscope Z: ");
    Serial.print(data.gyroZ);
    Serial.println(" °/s");
    Serial.println("--------------------------------");
  }
}

