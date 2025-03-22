#include <SPI.h>
#include <RH_RF69.h>

// set radio frequency
#define RF69_FREQ     867500000

// specify pins
#define RFM69_CS      6
#define RFM69_INT     9
#define RFM69_RST     10
#define LED           13

RH_RF69 rf69(RFM69_CS, RFM69_INT);

int32_t packetnum = 0; // packet counter

void setup() {
  Serial.begin(9600);

  init_radio_module();
}

void loop() {
 if (rf69.available()) { 
    uint8_t buf[50];
    uint8_t len = sizeof(buf);

    if (rf69.recv(buf, &len)) {
      if (!len) return;

      // print received data with added RSSI value
      buf[len] = 0;

      Serial.print("$");
      Serial.print(rf69.lastRssi(), DEC);
      Serial.print(",");
      Serial.print((char*)buf);
      Serial.print("\r\n");

      // send reply
      uint8_t data[] = "ACK";

      rf69.send(data, sizeof(data));
      rf69.waitPacketSent();

      Blink(LED, 50, 1);
    }
  }
}

void Blink(byte PIN, byte DELAY_MS, byte loops) {
  for (byte i = 0;i < loops; i++)  {
    digitalWrite(PIN,HIGH);
    delay(DELAY_MS);
    digitalWrite(PIN,LOW);
    delay(DELAY_MS);
  }
}

void init_radio_module() {
  pinMode(LED, OUTPUT);     
  pinMode(RFM69_RST, OUTPUT);
  digitalWrite(RFM69_RST, LOW);

  digitalWrite(RFM69_RST, HIGH);
  delay(10);
  digitalWrite(RFM69_RST, LOW);
  delay(10);

  rf69.init();
  rf69.setFrequency(RF69_FREQ);
  rf69.setTxPower(16, true);  // power range: 14 - 20

  uint8_t key[] = { 
                    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08
                  };
  rf69.setEncryptionKey(key);
  
  pinMode(LED, OUTPUT);
}