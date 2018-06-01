/* 
 * Receiver for bathroom status. Gets status from transmitter and lights up
 * to indicate if bathroom is available
 * 
 * Runs on Uno
 */

#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>
#include <Adafruit_NeoPixel.h>

#define debugMode TRUE // activate serial output and additional tests if set to true

#define NUM_LEDS 12 // Number of leds on stick
#define LED_PIN 8 // Digital In (DI) of RGB Stick connected to pin 8 of the UNO

int ReceivedMessage[1] = {000}; // Used to store value received by the NRF24L01

RF24 radio(9,10); // NRF24L01 used SPI pins + Pin 9 and 10 on the UNO
const uint64_t pipe = 0xE6E6E6E6E6E6; // Needs to be the same for communicating between 2 NRF24L01 


void setup(){
  radio.begin(); // Start the NRF24L01
  radio.openReadingPipe(1,pipe); // Get NRF24L01 ready to receive
  radio.startListening(); // Listen to see if information received
  
  pinMode(LED_PIN, OUTPUT); // Set RGB Stick UNO pin to an OUTPUT

  // setup neopixels here
}

void loop(){
  while (radio.available()){
    radio.read(ReceivedMessage, 1); // Read information from the NRF24L01
    if (ReceivedMessage[0] == 1) { // Indicates door is closed
      for(int x = 0; x != NUM_LEDS; x++){
        leds[x] = CRGB::Green;
        FastLED.show();
      }
    }
    else {
      for(int x = 0; x != NUM_LEDS; x++) {
        leds[x] = CRGB::Red;
        FastLED.show();
      }
    }
  delay(10);
  }
}
