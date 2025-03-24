# EcoMaros CanSat Project

![EcoMaros Logo](link_to_logo_image_if_available)

## Table of Contents
- [Project Overview](#project-overview)
- [System Architecture](#system-architecture)
- [Hardware Components](#hardware-components)
  - [Main Board](#main-board)
  - [Sensors](#sensors)
  - [Communication Systems](#communication-systems)
  - [Power System](#power-system)
  - [Payload and Deployment Mechanism](#payload-and-deployment-mechanism)
- [Software Architecture](#software-architecture)
  - [Microcontroller Code](#microcontroller-code)
  - [Ground Station Software](#ground-station-software)
  - [Data Processing and Telemetry](#data-processing-and-telemetry)
- [Launch and Deployment](#launch-and-deployment)
- [Testing and Validation](#testing-and-validation)
- [Contributors](#contributors)
- [License](#license)

---

# 📡 EcoMaros CanSat – Project Overview

## 🌍 Introduction  
EcoMaros is a CanSat project developed for the European Space Agency’s CanSat competition. Our mission was to design, build, and launch a fully functional satellite the size of a soda can, carrying out both a **primary mission** (measuring atmospheric temperature and pressure) and a **secondary mission** (environmental air quality analysis).  

Our CanSat was launched from a rocket, reaching an altitude of approximately **1 km** before descending via parachute while continuously transmitting data to our ground station. The data collected was analyzed to extract valuable scientific insights and improve future small-satellite designs.  

## 🛠️ Mission Objectives  

### ✅ **Primary Mission:**  
- **Measure atmospheric temperature and pressure** throughout the descent.  
- **Log and transmit real-time data** to the ground station.  
- **Compare results with trusted meteorological sources** to ensure accuracy.  

### 🌿 **Secondary Mission:**  
- **Analyze air quality parameters** by measuring pollutants such as CO, CO₂, NO₂, and VOC levels.  
- **Monitor altitude-based variations** in air quality and correlate with temperature/pressure.  
- **Evaluate sensor efficiency** and compare with standardized environmental datasets.  

## 🛰️ Technical Summary  

Our CanSat consisted of **three primary systems**:  

1. **The CanSat Payload** (the satellite itself):  
   - Housed **sensors**, **microcontrollers**, and **power systems**.  
   - Collected, processed, and transmitted environmental data.  
   - Designed to survive high-G forces and impact upon landing.  

2. **The Descent System** (parachute and deployment mechanism):  
   - Ensured **stable descent** for optimal data collection.  
   - Designed for **predictable landing behavior** to facilitate recovery.  
   - Tested under real-world conditions with varying payload weights.  

3. **The Ground Station** (communication and data reception):  
   - Received **live telemetry** from the CanSat.  
   - Used **LoRa communication** at 868 MHz.  
   - Displayed data in **real-time dashboards** for analysis.  

## 🔬 Innovation & Unique Features  

- **Hybrid Communication System:** Combined LoRaWAN for real-time transmission with onboard SD card storage for redundancy.  
- **Optimized Air Quality Sensor Placement:** Minimized contamination and external interferences.  
- **Advanced Software Architecture:** Supported real-time data visualization and predictive modeling.  
- **Robust Mechanical Design:** Impact-resistant casing, secure wiring, and heat-resistant materials ensured durability.  

## 🚀 Development Phases  

1. **Design & Planning:** Component selection, CAD modeling, and circuit design.  
2. **Prototype Assembly:** Initial hardware integration and software development.  
3. **Ground Testing:** Component-level and full-system tests, including **environmental, communication, and structural validation**.  
4. **Flight Preparation:** Calibration, parachute testing, and mission simulations.  
5. **Launch & Data Analysis:** Real-world deployment, telemetry collection, and post-flight analysis.  


---

## System Architecture
The EcoMaros CanSat is composed of multiple subsystems working together to ensure a successful mission:
- **Sensing Unit:** Collects environmental data (temperature, pressure, humidity, altitude, etc.).
- **Processing Unit:** The microcontroller processes the sensor data and prepares it for transmission.
- **Communication Unit:** Transmits telemetry data to the ground station.
- **Power Unit:** Supplies power to all components.
- **Recovery System:** Ensures a safe landing.

### Block Diagram
```mermaid
graph TD;
    A[Power Supply] -->|Regulated Power| B[Microcontroller];
    B -->|I2C/SPI| C[Sensors];
    B -->|UART| D[Radio Module];
    B -->|Data Logging| E[SD Card];
    B -->|PWM| F[Servo for Deployment];
    D -->|Telemetry Data| G[Ground Station];
    G -->|Data Analysis| H[PC Software];
```

---

## Hardware Components

### Main Board
The main board houses the **microcontroller**, power management circuit, sensor interfaces, and communication modules. The microcontroller used is the **[insert model]**, chosen for its low power consumption and real-time processing capabilities.

### Sensors
The EcoMaros CanSat features multiple sensors for data collection:
- **Barometric Pressure Sensor:** [insert model], measures altitude and pressure.
- **Temperature and Humidity Sensor:** [insert model], ensures accurate environmental readings.
- **Accelerometer and Gyroscope:** [insert model], used for motion tracking.
- **Magnetometer:** [insert model], helps in orientation detection.
- **GPS Module:** [insert model], provides real-time positioning.

### Communication Systems
- **Radio Module:** The CanSat uses an [insert radio model] operating at [frequency] MHz for real-time telemetry transmission.
- **Antenna:** A custom-designed dipole antenna ensures reliable data transmission.

### Power System
- **Battery:** A lightweight [insert battery type and capacity] powers the CanSat.
- **Voltage Regulation:** A [insert regulator model] ensures stable power delivery.

### Payload and Deployment Mechanism
The payload consists of a scientific experiment designed to analyze environmental parameters during descent. A servo mechanism controls the deployment of the parachute.

---

## Software Architecture

### Microcontroller Code
The firmware running on the microcontroller handles sensor data acquisition, processing, and transmission. Key functionalities include:
- Initialization of sensors and communication protocols.
- Real-time data acquisition and processing.
- Transmission of telemetry data.

```c
void setup() {
    Serial.begin(9600);
    initSensors();
    initRadio();
}

void loop() {
    readSensors();
    sendTelemetry();
    delay(1000);
}
```

### Ground Station Software
The ground station software receives telemetry data and visualizes it in real-time.

```python
import serial

def read_telemetry():
    ser = serial.Serial('COM3', 9600)
    while True:
        data = ser.readline()
        print(data.decode())
```

### Data Processing and Telemetry
Data is structured as CSV packets and stored for further analysis. The telemetry format is:
```
Timestamp, Temperature, Pressure, Altitude, Humidity, GPS_Lat, GPS_Long
```

---

## Launch and Deployment
- **Pre-launch checks:** Ensuring all systems are functional.
- **Deployment:** The CanSat is released from an altitude of 1km.
- **Data collection:** Sensors record environmental parameters during descent.

---

## Testing and Validation
Extensive testing was conducted, including:
- Bench testing of sensors.
- Range testing of the radio module.
- Drop tests to validate parachute deployment.

---

## Contributors
- **[Team Member 1]** - Lead Engineer
- **[Team Member 2]** - Software Developer
- **[Team Member 3]** - Hardware Specialist

---

## License
This project is licensed under the MIT License - see the LICENSE file for details.

---

For more details, visit our [GitHub Repository](link_to_repo).
