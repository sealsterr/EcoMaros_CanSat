# EcoMaros CanSat Project

[![Instagram](https://img.shields.io/badge/Instagram-E4405F?style=for-the-badge&logo=instagram&logoColor=white)](https://www.instagram.com/ecomaros.cansat)
[![YouTube](https://img.shields.io/badge/YouTube-E4405F?style=for-the-badge&logo=youtube&logoColor=white)](https://www.youtube.com/@EcoMaros)
![GitHub Last Commit](https://img.shields.io/github/last-commit/sealsterr/EcoMaros_CanSat)

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
  - [Frequency Test](#frequency-test)
  - [Load Test](#load-test)
  - [Temperature & Pressure Sensor Test](#temperature--pressure-sensor-test)
  - [Camera Test](#camera-test)
  - [Air Quality Sensor Test](#air-quality-sensor-test)
  - [Parachute Test](#parachute-test)
  - [Acceleration Test](#acceleration-test)
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

1. **The CanSat** (the satellite itself):
   - Housed **sensors**, **microcontrollers**, and **power systems**.
   - Collected, processed, and transmitted environmental data.
   - Designed to survive high-G forces and impact upon landing.

2. **The Recovery System** (parachute):
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

![diagram](https://github.com/user-attachments/assets/65de76ea-d409-41e1-a82c-555c2a933c00)

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

![microcontroller](https://github.com/user-attachments/assets/92933c8d-502d-404f-8992-38a6901a05bf)

### 3️⃣ **Sensor Suite**
EcoMaros is equipped with a **diverse set of sensors** to ensure comprehensive environmental monitoring:

| Sensor | Function | Model |
|---------|------------|------------|
| **Barometric Pressure & Temperature Sensor** | Measures altitude and air temperature | BMP280 |
| **Air Quality Sensor** | Detects pollutants (CO₂, NO₂, VOCs) | MQ135 |
| **Accelerometer & Gyroscope** | Measures orientation, tilt, and G-forces | MPU6050 |
| **GPS Module** | Tracks real-time location and altitude | DFRobot Gravity GNSS |
| **Camera** | Records footage during the mission | ESP32 CAM |

![sensors](https://github.com/user-attachments/assets/a492b1d1-ece1-44d0-be50-1a7901423502)
![camera](https://github.com/user-attachments/assets/152019c6-4759-46c5-b4ce-38b5a3c0613f)

**Data Collection & Processing:**
- All sensor data is processed **every 200ms** and stored in CSV format.
- In case of radio failure, the data is alos logged to an **onboard SD card** for post-flight analysis.
- The onboard motion-detecting camera captures video data separately.

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

![radio](https://github.com/user-attachments/assets/a23925ce-eedc-4168-bab1-30cf6309c56d)

### 5️⃣ **Recovery System**
The CanSat is equipped with a **semi-spherical parachute** made of **ripstop nylon**, attached using a **tear-resistant tether system**.

**Parachute Deployment Sequence:**
1. The CanSat is ejected at **1000m altitude**.
2. The parachute deploys, slowing descent to **~7.5 m/s**.
3. The CanSat lands safely, with GPS data assisting in retrieval.

**Key Features:**
- **Metal hook attachment** for secure parachute connection.
- **Load-tested connection system** capable of withstanding **50N of force**.
- High-visibility **orange and white** color for easy retrieval.

![Parachute System](https://github.com/user-attachments/assets/70175fc9-f2ab-4462-8e77-28a96de25793)

---

# Testing

You can find additional images, videos, and graphs in the `Testing` folder within the main project repository.

## 1. 📶 Frequency Test

**Purpose:** To verify that the RFM69HCW radio module transmits within the designated 868 MHz ISM band, ensuring compliance with regulations.
*   **Procedure:**
    *   Connect the CanSat to a power source and activate telemetry transmission.
    *   Use a spectrum analyzer (Rigol DSA815) to capture the transmission spectrum.

*   **Expected Results:**
    *   Transmission centered precisely at 868.000 MHz, confirmed by the captured spectrum using the Rigol DSA815 Spectrum Analyzer.
    *   The captured spectrum confirms that our transmission is centered precisely at 868.000 MHz, with the signal strength peaking at -21.59 dBm, well within the acceptable limits for ISM-band operations
    *   The noise floor remains low, ensuring clean and stable communication
*   **Status:** Successful ✅
    ![freq_test_C](https://github.com/user-attachments/assets/1ecc7824-6a4d-4b2e-9f40-d2e22d12bf22)

## 2. 🏋️‍♂️ Load Test

**Purpose:** To ensure the parachute attachment point can withstand the forces experienced during deployment and descent.
*   **Procedure:**
    *   Attach the parachute to the CanSat.
    *   Connect the parachute tether to a weight equivalent to 5 kg
    *   Suspended the weight for an extended period while inspecting for any signs of material fatigue, deformation, or failure

*   **Expected Results:**
        *   The parachute attachment securely held the load without any visible weakening, ensuring that it will perform reliably under real launch conditions
*   **Status:** Successful ✅

## 3. Temperature & Pressure Sensor Test
**Purpose:** Validate accuracy of the BMP280 measuring unit.
*   **Procedure:**
    *   Power on the CanSat, including the BMP280 sensor
    *   Log initial measurements to textfile
    *   Compare its readings with established weather data, sourced from reputable meteorological websites

*   **Expected Results:**
    *   Values aligned within an acceptable margin of error, confirming the sensors' calibration and accuracy.

*   **Status:** Successful ✅

 Date     | Time     | Temperature (°C) | Pressure (hPa) | External Temp (°C) | External Pressure (hPa) |
 -------- | -------- | --------------- | --------------- | -------------------- | ----------------------- |
 2025-03-20 | 10:00:00 | 22.5            | 1012.3          | 22.0                 | 1012.0                |
 2025-03-20 | 10:00:10 | 22.6            | 1012.4          | 22.0                 | 1012.0                |
 2025-03-20 | 10:00:20 | 22.7            | 1012.5          | 22.1                 | 1012.1                |


## 4. 📸 Camera Test

**Purpose:** To evaluate the performance and stability of the ESP32, by taking multiple tests in different scenarios.
*   **Procedure:**
    *   Moving up and down the stairs, in order to simulate real-time CanSat movement
    *   Mount ESP32 Cam module to the CanSat, and recording the footage
    *   Analyzing the footage, is it clear and without interruptions
*   **Expected Results:**
    *   The camera effectively handled vibrations and sudden shifts
    *   The camera operated continuously within the expected mission duration, without overheating or interruptions.
*   **Status:** Successful ✅

[YouTube link](https://www.youtube.com/watch?v=rytZMgvs1aI)

## 5. 💨 Air Quality Sensor Test

**Purpose:** To verify the functionality and responsiveness of our air quality sensor. We conducted a controlled test by exposing it to varying air conditions and analyzing the received data, the test lasted 10 seconds.
*   **Procedure:**
    *   Place CanSat near exhaust source to simulate polluted conditions, and log all the data
*   **Expected Result:**
    *   Sensor data showed a response to the change, indicating a significant deviation from the baseline. Finally, we returned the CanSat to clean air, where the sensor readings gradually stabilized back to their initial values

*   **Status:** Successful ✅

![airquality](https://github.com/user-attachments/assets/b4cce326-8b2d-4ad9-a5ba-abd5c79580ea)


## 6. 🪂 Parachute Test

**Purpose:** To evaluate the deployment and descent characteristics of our parachute system.

*   **Procedure:**
     * Pack parachute, packing the parachute in its folded and secured state to simulate real launch conditions
     * Throw CanSat from the sky, conduct a field test using an older 3D-printed dummy version of the CanSat
     *Upon release, the parachute successfully unfolded, stabilizing the descent and demonstrating the effectiveness of both the packing method and the attachment points, the parachute's deployment in real world conditions

*   **Status:** Successful ✅

  ![parachute deployment](https://github.com/user-attachments/assets/d7375626-aacd-44d6-874a-f4595dd78d21)

## 7. ⚙️ Acceleration Test
*   **Purpose:** Assess the structural integrity of the CanSat under high acceleration forces by using a power drill.
*   **Procedure:** Attach the CanSat to a power drill and spinning it at high speed for a specified duration. By measuring the number of rotations within a set time frame, we calculated the angular velocity
*   **Status:** Successful. ✅

  [YouTube link](https://youtu.be/aheQlWmyFRo)

---

# Contributors

>We want to extend our deepest gratitude to everyone who has supported and contributed to our project. Your dedication, hard work, and generosity have been invaluable, and we truly appreciate the effort and time you’ve invested. Without your help, this journey wouldn’t have been possible! ♥️

- **Werner Haraszti - Lico Mecatronic S.R.L.** - technological, financial and equipment support
- **Fuccaro Miklós** - AutoCAD software coaching, IT support

---

# License
This project is licensed under the MIT License - see the LICENSE file for details.
