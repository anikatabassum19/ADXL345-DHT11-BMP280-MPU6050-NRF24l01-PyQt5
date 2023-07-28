# Wireless Sensor Data Transmission using NRF24l01

![Arduino Logo](https://www.arduino.cc/en/uploads/Arduino_logo.svg)

Welcome to the Wireless Sensor Data Transmission project using NRF24l01 modules for Arduino! This project demonstrates how to establish a wireless communication link between two Arduino boards, enabling seamless transmission of sensor data in real-time.

## Table of Contents

1. [Introduction](#introduction)
2. [Hardware Setup](#hardware-setup)
3. [Installation](#installation)
4. [Usage](#usage)
5. [Examples](#examples)
6. [Contributing](#contributing)
7. [License](#license)

## Introduction

Wireless sensor data transmission is crucial for various embedded system applications. This repository provides Arduino code for establishing a wireless communication link between two Arduino boards using NRF24l01 modules. The system can transmit sensor data from ADXL345, DHT11, BMP280, and MPU6050 sensors to another Arduino board acting as the receiver.

## Hardware Setup

1. **ADXL345**:
   - Library: [Adafruit ADXL345](https://github.com/adafruit/Adafruit_ADXL345)
   - Connect to Arduino:
     - VCC to 5V
     - GND to GND
     - SDA to A4 (Arduino Uno)
     - SCL to A5 (Arduino Uno)

2. **DHT11**:
   - Library: [DHT sensor library](https://github.com/adafruit/DHT-sensor-library)
   - Connect to Arduino:
     - VCC to 5V
     - GND to GND
     - Data pin to 2 (Arduino Uno)

3. **BMP280**:
   - Library: [Adafruit BMP280](https://github.com/adafruit/Adafruit_BMP280_Library)
   - Connect to Arduino:
     - VCC to 5V
     - GND to GND
     - SDA to A4 (Arduino Uno)
     - SCL to A5 (Arduino Uno)

4. **MPU6050**:
   - Library: [MPU6050_tockn](https://github.com/tockn/MPU6050_tockn)
   - Connect to Arduino:
     - VCC to 5V
     - GND to GND
     - SDA to A4 (Arduino Uno)
     - SCL to A5 (Arduino Uno)

5. **NRF24l01**:
   - Library: [TMRh20 RF24](https://github.com/nRF24/RF24)
   - Connect to Arduino:
     - VCC to 3.3V
     - GND to GND
     - CE to 7 (Arduino Uno)
     - CSN to 9 (Arduino Uno)
     - SCK to 13
     - MOSI to 11
     - MISO to 12

## Installation

1. Clone this repository to your local machine using `git clone`.

2. Install the necessary libraries for the ADXL345, DHT11, BMP280, MPU6050, and NRF24l01 modules in your Arduino IDE.

3. Upload the `Transmitter.ino` code to the Arduino board acting as the transmitter.

4. Upload the `Receiver.ino` code to the Arduino board acting as the receiver.

5. Power up both Arduino boards and the NRF24l01 modules.

## Usage

The wireless data transmission is automatically initiated once the transmitter and receiver are powered up, and the NRF24l01 modules establish a connection. The transmitter collects sensor data and sends it wirelessly to the receiver.

To view the received sensor data, open the Arduino Serial Monitor for the receiver board.

## Examples

- `Transmitter.ino`: This example code reads sensor data and sends it wirelessly to the receiver.

- `Receiver.ino`: This example code receives sensor data from the transmitter and displays it in the Serial Monitor.

## Contributing

We welcome your contributions! Feel free to open issues and pull requests.

## License

This repository is licensed under the [MIT License](LICENSE).
