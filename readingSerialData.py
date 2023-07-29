import serial

# Replace 'COMx' with the appropriate serial port name for your Arduino.
# On Windows, it will be something like 'COMx' (e.g., 'COM3').
# On macOS or Linux, it will be '/dev/ttyUSBx' or '/dev/ttyACMx'.
ser = serial.Serial('/dev/ttyACM1', 9600)  # Adjust the baud rate if needed

while True:
    line = ser.readline().decode().strip()
    if line.startswith("----- Received Sensor Data -----"):
        print(line)
        print(ser.readline().decode().strip())  # Temperature
        print(ser.readline().decode().strip())  # Humidity
        print(ser.readline().decode().strip())  # Pressure
        print(ser.readline().decode().strip())  # Altitude
        print(ser.readline().decode().strip())  # Acceleration X
        print(ser.readline().decode().strip())  # Acceleration Y
        print(ser.readline().decode().strip())  # Acceleration Z
        print(ser.readline().decode().strip())  # Gyroscope X
        print(ser.readline().decode().strip())  # Gyroscope Y
        print(ser.readline().decode().strip())  # Gyroscope Z
        print(ser.readline().decode().strip())  # Separator line
