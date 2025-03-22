#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <RH_RF69.h>
#include <SD.h>
#include <DFRobot_GNSS.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// specify pins
#define BMP_SCK     (13)
#define BMP_MISO    (12)
#define BMP_MOSI    (11)
#define BMP_CS      (10)

#define RFM69_CS    6
#define RFM69_INT   9
#define RFM69_RST   10
#define RADIO_LED   13

// set radio frequency
#define RF69_FREQ   867500000

const int chipSelect = 4;
int32_t packetnum = 0;

Adafruit_BMP280 bmp;
Adafruit_MPU6050 mpu;

RH_RF69 rf69(RFM69_CS, RFM69_INT);
DFRobot_GNSS_I2C gnss(&Wire ,GNSS_DEVICE_ADDR);

void setup() {
  Serial.begin(9600);

  // initialise modules
  init_radio_module();
  init_bmp_module();
  init_mpu_module();
  init_mq_module();
  init_sd_card();
  init_gnss_module();
}

void loop() {
  unsigned long ms = millis();

  String dataString = "";

  sensors_event_t a; // m / s^2
  sensors_event_t g; // rad / s
  sensors_event_t temp; // C

  mpu.getEvent(&a, &g, &temp);

  sTim_t date = gnss.getDate(); // Date
  sTim_t utc = gnss.getUTC(); // UTC Time
  sLonLat_t lat = gnss.getLat(); // Latitude
  sLonLat_t lon = gnss.getLon(); // Longitude
  double high = gnss.getAlt(); // Altitude - m
  double cog = gnss.getCog(); // Course over Ground - Degrees
  double sog = gnss.getSog() * 0.514; // Speed over Ground - m / s

  float temperature = bmp.readTemperature(); // C
  float pressure = bmp.readPressure() / 100; // hPa
  float altitude = bmp.readAltitude(1013.25); // m
  float airquality = analogRead(11); // PPM

  float gforce = sqrt((a.acceleration.x * a.acceleration.x) + (a.acceleration.y * a.acceleration.y) + (a.acceleration.z * a.acceleration.z)) - 11;
  // after testing we found that during a state of rest the sensor measured 11G's, so we removed the constant positive G-Force to maintain correct data measurement 

  // save data to SD card and format lines for data recovery and Serial Studio handling
  dataString += String(packetnum, DEC);
  dataString += ",";
  dataString += String(date.year);
  dataString += "/";
  dataString += String(date.month);
  dataString += "/";
  dataString += String(date.date);
  dataString += ",";
  dataString += String(utc.hour);
  dataString += ":";
  dataString += String(utc.minute);
  dataString += ":";
  dataString += String(utc.second);
  dataString += ",";
  dataString += String(lat.latitudeDegree, 6);
  dataString += ",";
  dataString += String(lon.lonitudeDegree, 6);
  dataString += ",";
  dataString += String(high, 1);
  dataString += ",";
  dataString += String(cog, 2);
  dataString += ",";
  dataString += String(sog, 2);
  dataString += ",";
  dataString += String(temperature, 1);
  dataString += ",";
  dataString += String(pressure, 1);
  dataString += ",";
  dataString += String(airquality, 0);
  dataString += ",";
  dataString += String(a.acceleration.x);
  dataString += ",";
  dataString += String(a.acceleration.y);
  dataString += ",";
  dataString += String(a.acceleration.z);
  dataString += ",";
  dataString += String(g.gyro.x);
  dataString += ",";
  dataString += String(g.gyro.y);
  dataString += ",";
  dataString += String(g.gyro.z);
  dataString += ",";
  dataString += String(gforce, 1);
  dataString += ";";

  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
  }

  // send and format telemetry data to Ground Station
  String packet_str = "";
  packet_str.concat(String(String(packetnum, DEC) + ","));
  packet_str.concat(String(lat.latitudeDegree, 6) + ",");
  packet_str.concat(String(lon.lonitudeDegree, 6) + ",");
  packet_str.concat(String(high, 1) + ";");

  rf69.send((uint8_t *)(packet_str.c_str()), packet_str.length());
  rf69.waitPacketSent();

  uint8_t buf[5];
  uint8_t len = sizeof(buf);

  if (rf69.waitAvailableTimeout(10))  { 
    if (rf69.recv(buf, &len)) {
        Serial.print(": ");
        Serial.println((char*)buf);
        Blink(RADIO_LED, 10, 1);
    } else {
        Serial.println("Receive failed");
        Serial.println();
        Blink(RADIO_LED, 10, 2);
    }
  } else {
      Serial.println("No reply, is another RFM69 listening?");
      Serial.println();
      Blink(RADIO_LED, 10, 3); 
  }

  packetnum += 1;
  delay(100);
}

void init_radio_module() {
  pinMode(RADIO_LED, OUTPUT);     
  pinMode(RFM69_RST, OUTPUT);
  digitalWrite(RFM69_RST, LOW);

  digitalWrite(RFM69_RST, HIGH);
  delay(10);
  digitalWrite(RFM69_RST, LOW);
  delay(10);
  
  rf69.init();
  rf69.setFrequency(RF69_FREQ)
  rf69.setTxPower(16, true); // power range: 14 - 20

  uint8_t key[] = {
                    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08
                  };
  rf69.setEncryptionKey(key);
  
  pinMode(RADIO_LED, OUTPUT);
}

void init_bmp_module() {
  unsigned status;

  status = bmp.begin();
  bmp.setSampling(
                  Adafruit_BMP280::MODE_NORMAL,     
                  Adafruit_BMP280::SAMPLING_X2,     
                  Adafruit_BMP280::SAMPLING_X16,   
                  Adafruit_BMP280::FILTER_X16,      
                  Adafruit_BMP280::STANDBY_MS_500
                );
}

void init_gnss_module() {
  gnss.begin();
  gnss.enablePower(); 
  gnss.setGnss(eGPS_BeiDou_GLONASS); 
  gnss.setRgbOn();
}

void init_mpu_module() {
  mpu.begin();
  // setting sensor ranges
  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_2000_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void init_mq_module() {
  pinMode(11, INPUT);
}

void init_sd_card() {
  SD.begin(chipSelect);
}

void Blink(byte pin, byte delay_ms, byte loops) {
  while (loops--) {
    digitalWrite(pin, HIGH);
    delay(delay_ms);
    digitalWrite(pin, LOW);
    delay(delay_ms);
  }
}