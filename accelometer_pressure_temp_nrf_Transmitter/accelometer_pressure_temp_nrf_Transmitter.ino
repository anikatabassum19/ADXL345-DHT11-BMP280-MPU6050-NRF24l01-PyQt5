#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <DHT.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_ADXL345_U.h>
#include <MPU6050.h>

#define DHTPIN 2        // Pin connected to the DHT11 data pin
#define DHTTYPE DHT11   // DHT11 sensor type
DHT dht(DHTPIN, DHTTYPE);

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

Adafruit_BMP280 bmp; // Create BMP280 instance
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345); // Create ADXL345 instance
MPU6050 mpu; // Create MPU6050 instance

void setup() {
  Serial.begin(9600);
  dht.begin();
  Wire.begin();
  radio.begin();
  radio.openWritingPipe(0xF0F0F0F0E1LL);  // Set the address for communication
  radio.setPALevel(RF24_PA_HIGH);  // Set the power amplifier level
  radio.stopListening();  // Put the module in transmitting mode

  // Initialize BMP280
  if (!bmp.begin(0x76)) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }

  // Initialize ADXL345
  if (!accel.begin()) {
    Serial.println(F("Could not find a valid ADXL345 sensor, check wiring!"));
    while (1);
  }
  accel.setRange(ADXL345_RANGE_16_G);

  // Initialize MPU6050
  mpu.initialize();
  mpu.setXGyroOffset(0);
  mpu.setYGyroOffset(0);
  mpu.setZGyroOffset(0);
}

void loop() {
  float temperature = dht.readTemperature();  // Read temperature value
  float humidity = dht.readHumidity();        // Read humidity value

  // BMP280: Read pressure and altitude
  float pressure = bmp.readPressure() / 100.0F; // Pa to hPa conversion
  float altitude = bmp.readAltitude(1013.25); // Adjusted for your local pressure

  // ADXL345: Read accelerometer data
  sensors_event_t event;
  accel.getEvent(&event);
  float accelerationX = event.acceleration.x;
  float accelerationY = event.acceleration.y;
  float accelerationZ = event.acceleration.z;

  // MPU6050: Read gyroscope data
  int16_t gx, gy, gz;
  mpu.getRotation(&gx, &gy, &gz);
  float gyroX = gx / 131.0; // Sensitivity scale factor for 250 degrees/s
  float gyroY = gy / 131.0;
  float gyroZ = gz / 131.0;

  SensorData data;
  data.temperature = temperature;
  data.humidity = humidity;
  data.pressure = pressure;
  data.altitude = altitude;
  data.accelerationX = accelerationX;
  data.accelerationY = accelerationY;
  data.accelerationZ = accelerationZ;
  data.gyroX = gyroX;
  data.gyroY = gyroY;
  data.gyroZ = gyroZ;

  bool success = radio.write(&data, sizeof(data));  // Send the data

  if (success) {
    Serial.println("Message sent successfully.");
  } else {
    Serial.println("Failed to send message.");
  }

  delay(2000);  // Wait for 2 seconds before sending the next reading
}

