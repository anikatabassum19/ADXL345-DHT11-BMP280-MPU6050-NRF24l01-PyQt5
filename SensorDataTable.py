import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QTableWidget, QTableWidgetItem, QVBoxLayout, QWidget
from PyQt5.QtCore import Qt, QTimer
import serial

class SensorDataReader(QMainWindow):
    def __init__(self, port='/dev/ttyACM1', baud_rate=9600):
        super().__init__()

        self.serial_port = serial.Serial(port, baud_rate)
        self.sensor_data_list = []  # List to store all sensor data as dictionaries

        self.table = QTableWidget(self)
        self.table.setColumnCount(0)  # Number of columns will be set dynamically
        self.table.setHorizontalHeaderLabels([])

        layout = QVBoxLayout()
        layout.addWidget(self.table)

        widget = QWidget(self)
        widget.setLayout(layout)
        self.setCentralWidget(widget)

        self.update_table()

        self.timer = QTimer(self)
        self.timer.timeout.connect(self.update_table)
        self.timer.start(1000)  # Update table every 1000ms (1 second)

    def update_table(self):
        line = self.serial_port.readline().decode().strip()
        if line.startswith("----- Received Sensor Data -----"):
            sensor_data = {}
            for _ in range(9):
                data_line = self.serial_port.readline().decode().strip()
                sensor, value = data_line.split(": ")
                sensor_data[sensor] = value

            self.sensor_data_list.append(sensor_data)  # Add current data to the list
            self.show_sensor_data()

    def show_sensor_data(self):
        if len(self.sensor_data_list) == 0:
            return

        # Get all unique sensors from the data list
        all_sensors = set().union(*(data.keys() for data in self.sensor_data_list))

        if self.table.columnCount() == 0:
            # Set up table columns if not already set
            self.table.setColumnCount(len(all_sensors) + 1)  # Add an extra column for timestamp
            header_labels = ["Timestamp"] + list(all_sensors)
            self.table.setHorizontalHeaderLabels(header_labels)

        # Populate the table with the data
        row_count = len(self.sensor_data_list)
        self.table.setRowCount(row_count)
        for row, data in enumerate(self.sensor_data_list):
            timestamp_item = QTableWidgetItem(str(row + 1))  # Use row number as timestamp
            self.table.setItem(row, 0, timestamp_item)
            for col, sensor in enumerate(all_sensors, start=1):
                value = data.get(sensor, "")
                value_item = QTableWidgetItem(value)
                self.table.setItem(row, col, value_item)


if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = SensorDataReader()
    window.show()
    sys.exit(app.exec_())
