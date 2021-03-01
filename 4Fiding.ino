/*
  Fading

  This example shows how to fade an LED using the analogWrite() function.

  The circuit:
  - LED attached from digital pin 9 to ground.

  created 1 Nov 2008
  by David A. Mellis
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Fading
*/

const int ledPin =  16;      // D0-l1 the number of the LED pin
const int ledPin2 =  4;      // D2-l2 the number of the LED pin
int sensorValue = 0.3;  // variable to store the value coming from the sensor
int sensorPin = A0;    // select the input pin for the potentiometer

void setup() {
  // nothing happens in setup
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // fade in from min to max in increments of 5 points:
  for (int fadeValue = 0 ; fadeValue <= 1023; fadeValue += 5) {
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);

    delay(sensorValue);
    
    // wait for 30 milliseconds to see the dimming effect
//    delay(30);
  }

  // fade out from max to min in increments of 5 points:
  for (int fadeValue = 1023 ; fadeValue >= 0; fadeValue -= 5) {
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);
    
    delay(sensorValue);
    
    // wait for 30 milliseconds to see the dimming effect
//    delay(30);
  }
}
