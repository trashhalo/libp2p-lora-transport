#include <SPI.h>
#include <LoRa.h>

/* LibP2P LoRa Transport Arduino Bridge
 * Enables a LibP2P node to send messages over LoRa and possibly LoRaWAN.
 * Data coming in through the serial interface leaves through the LoRa radio
 * Data coming in through the LoRa radio exits the serial interface
 */

#define BAND 915E6
#define SYNC 0x99
#define SF 7
#define TXPOWER 20
#define SIGBW 250E3
#define DATASENT "data sent"
/*
API documentation: https://github.com/sandeepmistry/arduino-LoRa/blob/master/API.md
*/

void setup() {
    Serial.begin(9600);
    while (!Serial);
    LoRa.begin(BAND);
    LoRa.setSyncWord(SYNC);
    LoRa.setSpreadingFactor(SF);
    LoRa.setTxPower(TXPOWER);
  //  LoRa.setSignalBandwidth(SIGBW);
    Serial.println("ready");
}

void loop() {
  // try to parse packet
  if (LoRa.parsePacket()) {
    //String message = "received packet: rssi " + String(LoRa.packetRssi()) + " snr " + String(LoRa.packetSnr()) + " freq error " + String(LoRa.packetFrequencyError());
    Serial.println(LoRa.readString());
  } else if (Serial.available()) {
    if (LoRa.beginPacket()) { // beginPacket returns 1 if ready to proceed, so wait until radio is ready
        LoRa.print(Serial.readString());
        LoRa.endPacket(true); // async mode
        Serial.println(DATASENT);
    } 
  }
 // delay(1);
}