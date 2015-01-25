/* Vibe Sensor with LED Readout
  
  This sketch senses vibrations from a piezo element and prints the results to an LCD.
 
  Originally built with a SprkFun Redboard SIK, and a few extra parts.
  
  Based on 
  http://www.arduino.cc/en/Tutorial/Knock 
  and 
  https://learn.sparkfun.com/tutorials/sik-experiment-guide-for-arduino---v32/experiment-15-using-an-lcd

  ----- from the Knock sketch ------------------- stat
   This sketch reads a piezo element to detect a knocking sound. 
   It reads an analog pin and compares the result to a set threshold. 
   If the result is greater than the threshold, it writes
   "knock" to the serial port, and toggles the LED on pin 13.
  
   The circuit:
    * + connection of the piezo attached to analog in 0
    * - connection of the piezo attached to ground
    * 1-megohm resistor attached from analog in 0 to ground

   http://www.arduino.cc/en/Tutorial/Knock
   
   created 25 Mar 2007
   by David Cuartielles <http://www.0j0.org>
   modified 30 Aug 2011
   by Tom Igoe
   
   This example code is in the public domain.
  ----- from the Knock sketch ------------------- end

 */
 
#include <LiquidCrystal.h>

// these constants won't change:
const int ledPin = 13;      // led connected to digital pin 13
const int knockSensor = A0; // the piezo is connected to analog pin 0
const int threshold = 10;   // threshold value to decide when the detected sound is a knock or not

// these variables will change:
int sensorReading = 0;      // variable to store the value read from the sensor pin
int ledState = LOW;         // variable used to store the last LED status, to toggle the light

// Initialize the library with the pins we're using.
// (Note that you can use different pins if needed.)
// See http://arduino.cc/en/Reference/LiquidCrystal
// for more information:
LiquidCrystal lcd(12,11,5,4,3,2);

void knock_setup() {
  pinMode(ledPin, OUTPUT); // declare the ledPin as as OUTPUT
  Serial.begin(9600);      // use the serial port
}

void lcd_setup()
{
  // The LiquidCrystal library can be used with many different
  // LCD sizes. We're using one that's 2 lines of 16 characters,
  // so we'll inform the library of that:
  
  lcd.begin(16, 2);

  // Data sent to the display will stay there until it's
  // overwritten or power is removed. This can be a problem
  // when you upload a new sketch to the Arduino but old data
  // remains on the display. Let's clear the LCD using the
  // clear() command from the LiquidCrystal library:

  lcd.clear();

  // Now we'll display a message on the LCD!
  
  // Just as with the Arduino IDE, there's a cursor that
  // determines where the data you type will appear. By default,
  // this cursor is invisible, though you can make it visible
  // with other library commands if you wish.
  
  // When the display powers up, the invisible cursor starts 
  // on the top row and first column.
  
  lcd.print("hello, world!");

  // Adjusting the contrast (IMPORTANT!)
  
  // When you run the sketch for the first time, there's a
  // very good chance you won't see anything on the LCD display.
  // This is because the contrast likely won't be set correctly.
  // Don't worry, it's easy to set, and once you set it you won't
  // need to change it again.

  // Run the sketch, then turn the potentiometer until you can
  // clearly see the "hello, world!" text. If you still can't
  // see anything, check all of your connections, and ensure that
  // the sketch was successfully uploaded to the Arduino.
}

void setup() {
  knock_setup();
  lcd_setup();
}

void knock_loop() {
  // read the sensor and store it in the variable sensorReading:
  sensorReading = analogRead(knockSensor);    
  
  // if the sensor reading is greater than the threshold:
  if (sensorReading >= threshold) {
    // toggle the status of the ledPin:
    ledState = !ledState;   
    // update the LED pin itself:        
    digitalWrite(ledPin, ledState);
    // show useful stuff on the computer
    Serial.print("Sensor Reaidng: ");
    Serial.println(sensorReading);
    // delay so serial not overloaded
    delay(50);
  }
}

void lcd_loop()
{
  // You can move the invisible cursor to any location on the
  // LCD before sending data. Counting starts from 0, so the top
  // line is line 0 and the bottom line is line 1. Columns range
  // from 0 on the left side, to 15 on the right.

  // In additon to the "hello, world!" printed above, let's
  // display a running count of the seconds since the Arduino
  // was last reset. Note that the data you send to the display
  // will stay there unless you erase it by overwriting it or
  // sending a lcd.clear() command.
  
  // Here we'll set the invisible cursor to the first column
  // (column 0) of the second line (line 1):

  lcd.setCursor(0,1);

  // Now we'll print the number of seconds (millis() / 1000)
  // since the Arduino last reset:

  lcd.print(millis()/1000);

  // TIP: Since the numeric data we're sending is always growing
  // in length, new values will always overwrite the previous ones.
  // However, if you want to display varying or decreasing numbers
  // like a countdown, you'll find that the display will leave
  // "orphan" characters when the new value is shorter than the
  // old one.
  
  // To prevent this, you'll need to erase the old number before
  // writing the new one. You can do this by overwriting the
  // last number with spaces. If you erase the old number and
  // immediately write the new one, the momentary erase won't 
  // be noticeable. Here's a typical sequence of code:
  
  // lcd.setCursor(0,1);   // Set the cursor to the position
  // lcd.print("       "); // Erase the largest possible number
  // lcd.setCursor(0,1);   // Reset the cursor to the original position
  // lcd.print(millis()/1000); // Print our value
  
  // NEXT STEPS:

  // Now you know the basics of hooking up an LCD to the Arduino,
  // and sending text and numeric data to the display!

  // The LCD library has many commands for turning the
  // cursor on and off, scrolling the screen, etc. See:
  // http://arduino.cc/en/Reference/LiquidCrystal
  // for more information.
  
  // Arduino also comes with a number of built-in examples
  // showing off the features of the LiquidCrystal library.
  // These are locted in the file/examples/LiquidCrystal menu.

  // Have fun, and let us know what you create!
  // Your friends at SparkFun.
}

void loop() {
  knock_loop();
  lcd_loop();
}


