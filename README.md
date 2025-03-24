# EcoMaros CanSat Project

![GitHub Last Commit](https://img.shields.io/github/last-commit/sealsterr/EcoMaros_CanSat)
[![Instagram](https://img.shields.io/badge/Instagram-E4405F?style=for-the-badge&logo=instagram&logoColor=white)](https://www.instagram.com/ecomaros.cansat)


Our team's project for the 2025 CanSat Hungary Competition.

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
  - [Data Processing and Telemetry](#data-processing)
- [Testing](#testing)
- [Contributors](#contributors)
- [License](#license)

---

# Project Overview

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
- **Capture high-resolution video footage** during descent using an onboard camera, providing visual data to complement sensor readings and assist in post-mission analysis.  

## 🛰️ Technical Summary  

Our CanSat consisted of **three primary systems**:  

1. **The CanSat Payload** (the satellite itself):  
   - Housed **sensors**, **microcontrollers**, and **power systems**.  
   - Collected, processed, and transmitted environmental data.  
   - Designed to survive high-G forces and impact upon landing.  

2. **The Descent System** (parachute system):  
   - Ensured **stable descent** for optimal data collection.  
   - Tested under real-world conditions.  

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

# System Architecture  

The EcoMaros CanSat consists of multiple integrated subsystems, each playing a critical role in the mission. The architecture is designed to ensure efficient data collection, processing, and communication while maintaining structural integrity during descent.  

## 🖥️ Block Diagram  

The following diagram illustrates the overall architecture of the CanSat system, highlighting interactions between subsystems:  

![System Architecture Diagram](link_to_extracted_image_from_pdf)  

## 🛰️ Subsystem Overview  

### 1️⃣ **Power Management System**  
The CanSat operates using **two independent power sources**:  
- **2000mAh 3.7V LiPo Battery:** Supplies power to the microcontroller, sensors, and radio transmitter.  
- **1000mAh 3.7V LiPo Battery:** Dedicated to powering the onboard camera.  
A **step-up voltage booster** (3.7V → 5V) ensures that the camera receives stable voltage for optimal performance.  

**Key Features:**  
- Dual power system ensures redundancy and extended operation time.  
- Low-power microcontroller for optimized energy consumption.  
- Integrated master switch to safely power the CanSat on/off.  

### 2️⃣ **Microcontroller & Processing Unit**  
The heart of the CanSat is the **Adafruit Feather M0 Adalogger**, which:  
- Manages sensor data acquisition.  
- Controls power distribution.  
- Handles real-time telemetry transmission.  
- Logs data onto the onboard SD card.  

![Microcontroller and Wiring](link_to_microcontroller_diagram_from_pdf)  

### 3️⃣ **Sensor Suite**  
EcoMaros is equipped with a **diverse set of sensors** to ensure comprehensive environmental monitoring:  

| Sensor | Function | Model |  
|---------|------------|------------|  
| **Barometric Pressure & Temperature Sensor** | Measures altitude and air temperature | BMP280 |  
| **Air Quality Sensor** | Detects pollutants (CO₂, NO₂, VOCs) | MQ135 |  
| **Accelerometer & Gyroscope** | Measures orientation, tilt, and G-forces | MPU6050 |  
| **GPS Module** | Tracks real-time location and altitude | DFRobot Gravity GNSS |  

**Data Collection & Processing:**  
- All sensor data is processed **every 200ms** and stored in CSV format.  
- In case of radio failure, the data is logged to an **onboard SD card** for post-flight analysis.  
- The onboard motion-detecting camera captures video data separately.  

![Sensor Integration](link_to_sensor_wiring_image_from_pdf)  

### 4️⃣ **Communication System**  
The CanSat transmits real-time telemetry data using an **RFM69HCW 868 MHz radio module**, connected to a **5 dBi dipole antenna**.  

**Communication Flow:**  
1. Sensor data is processed by the microcontroller.  
2. Data packets are formatted and transmitted via the **RFM69HCW module**.  
3. The **ground station receiver** decodes and logs incoming data.  

**Key Features:**  
- **LoRa modulation** for long-range, low-power data transmission.  
- Configurable transmission frequency for interference mitigation.  
- Ground station software displays real-time telemetry graphs.  

![Radio Communication System](link_to_radio_module_diagram_from_pdf)  

### 5️⃣ **Recovery & Descent System**  
The CanSat is equipped with a **semi-spherical parachute** made of **ripstop nylon**, attached using a **tear-resistant tether system**.  

**Parachute Deployment Sequence:**  
1. The CanSat is ejected at **1000m altitude**.  
2. The parachute deploys, slowing descent to **~7.5 m/s**.  
3. The CanSat lands safely, with GPS data assisting in retrieval.  

**Key Features:**  
- **Metal hook attachment** for secure parachute connection.  
- **Load-tested connection system** capable of withstanding **50N of force**.  
- High-visibility **orange and white** color for easy retrieval.  

![Parachute System](link_to_parachute_test_image_from_pdf)  

## 🔄 Data Flow Diagram  

The diagram below outlines the data collection, transmission, and logging process within the CanSat system:

IDE KEP A CHARTROL

---

# Hardware Components

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

# Software Architecture

## Microcontroller Code
The firmware running on the microcontroller handles sensor data acquisition, processing, and transmission. Key functionalities include:
- Initialization of sensors and communication protocols.
  
  ```c
  void setup() {
    Serial.begin(9600);
  
    // initialize modules
    init_radio_module();
    init_bmp_module();
    init_mpu_module();
    init_mq_module();
    init_sd_card();
    init_gnss_module();
  }
  ```
  
- Real-time data acquisition and processing.

  ```c
  sensors_event_t a; // m/s^2
  sensors_event_t g; // rad/s
  sensors_event_t temp; // C

  mpu.getEvent(&a, &g, &temp);

  sTim_t date = gnss.getDate(); // Date
  sTim_t utc = gnss.getUTC(); // UTC Time
  sLonLat_t lat = gnss.getLat(); // Latitude
  sLonLat_t lon = gnss.getLon(); // Longitude
  double high = gnss.getAlt(); // Altitude - m
  double cog = gnss.getCog(); // Course over Ground - Degrees
  double sog = gnss.getSog() * 0.514; // Speed over Ground - m/s

  float temperature = bmp.readTemperature(); // C
  float pressure = bmp.readPressure() / 100; // hPa
  float altitude = bmp.readAltitude(1015.24); // m
  float airquality = analogRead(11); // PPM

  float gforce = sqrt((a.acceleration.x * a.acceleration.x) + (a.acceleration.y * a.acceleration.y) + (a.acceleration.z * a.acceleration.z)) - 11;
  // after testing we found that during a state of rest the sensor measured 11G's, so we removed the constant positive G-Force to maintain correct data measurement
  ```
  
- Transmission of telemetry data.

  ```c
  String packet_str = "";
  packet_str.concat(String(String(packetnum, DEC) + ","));
  packet_str.concat(String(lat.latitudeDegree, 6) + ",");
  packet_str.concat(String(lon.lonitudeDegree, 6) + ",");
  packet_str.concat(String(high, 1) + ",");
  ```

## Ground Station Software
The ground station software receives telemetry data and prints it on the Serial Monitor, adding an additional RSSI value.

```c
// print received data with added RSSI value
buf[len] = 0;

Serial.print("$");
Serial.print(rf69.lastRssi(), DEC);
Serial.print(",");
Serial.print((char*)buf);
Serial.print("\r\n");
```

## Data Processing
Data is stored in a `DATALOG.txt` file, every line representing a value, with a comma as separator. This enables us to use Microsoft Excel to organise data in a more friendly environment, making it compatible with our **Ground Processing Software**.

- **CanSat measurement format:**
```
Packet Number, Date, Time, Course over Ground, Speed over Ground, Temperature, Pressure, Air Quality, Latitude, Longitude, GPS Altitude, Accelerometer X-Y-Z & Gyroscope X-Y-Z, G-Force, BMP Altitude
```

- **Telemetry format:**
```
RSSI, Packet Number, Latitude, Longitude, GPS Altitude
```

- **Ground Processing Software:**
  
  In order to visualise and interpret incoming and stored data, our team decided to use [Serial Studio](https://github.com/Serial-Studio/Serial-Studio). This program enables us to record, replay and store incoming data, making post-launch data analysis much easier to conduct. During Serial Studio setup, we have to specify which "preset" we want to use. We have created two custom JSON files:

1. `ground_station_live.json`
  - Used during the CanSat competition launch, designed to receive and visualise telemetry data.\
    ![image](https://github.com/user-attachments/assets/cbb7d6a8-1102-4d99-b409-d3c9db9a8bfe)
2. `ground_station_playback.json`
  - Crucial for documentation and post-launch data showcase.
  - Played a crucial role when presenting our measured data to the jury.\
    ![image](https://github.com/user-attachments/assets/8c669c74-06ce-4a34-9763-0dd3750603b3)
---

# Testing

## 1. Frequency test

## 2. Load test

## 3. Temperature & pressure sensor test

## 4. Camera test

## 5. Air quality sensor test

## 6. Parachute test

## 7. Acceleration test

---

# Contributors

>We want to extend our deepest gratitude to everyone who has supported and contributed to our project. Your dedication, hard work, and generosity have been invaluable, and we truly appreciate the effort and time you’ve invested. Without your help, this journey wouldn’t have been possible. Thank you for being a part of our success! ♥️

- **Werner Haraszti - Lico Mecatronic S.R.L.** - technological, financial and equipment support
- **Fuccaro Miklós** - AutoCAD software coaching, IT support
  
---

# License
This project is licensed under the MIT License - see the LICENSE file for details.
