#include <Arduino.h>
#include <RF24.h>

// Pin definitions for nRF24L01

#define CE_PIN 19
#define CSN_PIN 18

// Create an instance of RF24
RF24 radio(CE_PIN, CSN_PIN);

// Addresses for the 2 nodes to communicate.
const uint64_t pipes[2] = {0xEEDDCCBBD2LL,0xEEDDCCBBAALL };

void setup() {
  Serial.begin(9600);
  delay(3000);
  Serial.print(SCK);
  Serial.println(MISO);
  Serial.println(MOSI);
  // Initialize the RF24 module
  radio.begin();
  
  // Set the module to PTXPRX mode
  radio.enableDynamicPayloads();
  radio.setRetries(15, 15);
  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1, pipes[1]);
  radio.startListening();
}

void loop() {
  // Send a message
  String message = "Hello from ESP32";
  radio.stopListening();
  radio.write(&message, sizeof(message));
  radio.startListening();
  
  // Check if a message is available
  if (radio.available()) {
    // Read the incoming message
    String incomingMessage;
    radio.read(&incomingMessage, sizeof(incomingMessage));
    Serial.println(incomingMessage);
  }

  delay(1000);
}