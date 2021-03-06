/* Vibe Sensor with LED Readout
  
  This sketch senses vibrations from a piezo element and prints the results to an LCD.
 
  Originally built with a SprkFun Redboard SIK, and a few extra parts.
  
  Based on 
  http://www.arduino.cc/en/Tutorial/Knock 
  and 
  https://learn.sparkfun.com/tutorials/sik-experiment-guide-for-arduino---v32/experiment-15-using-an-lcd

  IMPORTANT NOTE
  Connect the piezo sensor directly to the board so it is not near the LCD.
  When I wired it on the breadboard along with the LCD, the analogRead got 
  values between 10 and 22 just from the interference.
  
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

  ----- from the Sparkfun LCD sketch ------------------- stat
  
  SparkFun Inventor's Kit
  Example sketch 15
  
  LIQUID CRYSTAL DISPLAY (LCD)
  
    A Liquid Crystal Display (LCD) is a sophisticated module 
    that can be used to display text or numeric data. The display
    included in your SIK features two lines of 16 characters, and
    a backlight so it can be used at night.
  
    If you've been using the Serial Monitor to output data,
    you'll find that a LCD provides many of the same benefits
    without needing to drag a large computer around.
    
    This sketch will show you how to connect an LCD to your Arduino
    and display any data you wish.
  
  Hardware connections:
  
    The LCD has a 16-pin male header attached to it along the top
    edge. Pin 1 is the pin closest to the corner of the LCD.
    Pin 16 is the pin closest to the center of the LCD.
    
    Plug the LCD into your breadboard.
    
    As usual, you will want to connect the + and - power rails
    on the side of the breadboard to 5V and GND on your Arduino.
    
    Plug your 10K potentiometer into three unused rows on your
    breadboard. Connect one side of the potentiometer to 5V,
    and the other side to GND (it doesn't matter which). When you
    run this sketch, you'll use the potentiometer to adjust the
    contrast of the LCD so you can see the display.
  
    Now connect the LCD pins. Remember that pin 1 on the LCD
    is the one closest to the corner. Start there and work your
    way up.
    
    1 to GND
    2 to 5V
    3 to the center pin on the potentiometer
    4 to Arduino digital pin 12
    5 to GND
    6 to Arduino digital pin 11
    7 (no connection)
    8 (no connection)
    9 (no connection)
    10 (no connection)
    11 to Arduino digital pin 5
    12 to Arduino digital pin 4
    13 to Arduino digital pin 3
    14 to Arduino digital pin 2
    15 to 5V
    16 to GND
  
    Once everything is connected, load this sketch into the
    Arduino, and adjust the potentiometer until the display
    is clear.
  
  Library
  
    The LCD has a chip built into it that controls all the
    individual dots that make up the display, and obeys commands
    sent to it by the the Arduino. The chip knows the dot patterns
    that make up all the text characters, saving you a lot of work.
    
    To communicate with this chip, we'll use the LiquidCrystal
    library, which is one of the standard libraries that comes
    with the Arduino. This library does most of the hard work
    of interfacing to the LCD; all you need to pick a location
    on the display and send your data!
    
  Tips
  
    The LCD comes with a protective film over the display that
    you can peel off (but be careful of the display surface as
    it scratches easily).
    
    The LCD has a backlight that will light up when you turn on
    your Arduino. If the backlight doesn't turn on, check your 
    connections.
  
    As we said above, the potentiometer adjusts the contrast of
    the display. If you can't see anything when you run the sketch,
    turn the potentiometer's knob until the text is clear.
    
  This sketch was written by SparkFun Electronics,
  with lots of help from the Arduino community.
  This code is completely free for any use.
  Visit http://learn.sparkfun.com/products/2 for SIK information.
  Visit http://www.arduino.cc to learn about the Arduino.
  
  Version 1.0 2/2013 MDG
  ----- from the Sparkfun LCD sketch ------------------- end
 */
 
#include <LiquidCrystal.h>

// these constants won't change:
const boolean debug = false;
const int ledPin = 13;      // led connected to digital pin 13
const int knockSensor = A0; // the piezo is connected to analog pin 0
const int threshold = 5;   // threshold value to decide when the detected sound is a knock or not
const unsigned long initTime = millis();   // used in calculation of elapsed time

// these variables will change:
int sensorReading = 0;      // variable to store the value read from the sensor pin
int ledState = LOW;         // variable used to store the last LED status, to toggle the light
int readCount = 0;
int vibeCount = 0;
long lastReadTime = 0;   // used in calculation of elapsed time

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
  // setup display size
  lcd.begin(16, 2);

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Vibrations:");
  
  lcd.setCursor(0,1);
  lcd.print("Time:");

  // Adjusting the contrast (IMPORTANT!)
  
  // When you run the sketch for the first time, there's a
  // very good chance you won't see anything on the LCD display.
  // This is because the contrast likely won't be set correctly.
  // Don't worry, it's easy to set, and once you set it you won't
  // need to change it again.

  // Run the sketch, then turn the potentiometer until you can
  // clearly see the text. If you still can't
  // see anything, check all of your connections, and ensure that
  // the sketch was successfully uploaded to the Arduino.
}

void setup() {
  knock_setup();
  lcd_setup();
  Serial.println("Readings...");
}

void knock_loop() {
  // read the sensor and store it in the variable sensorReading:
  sensorReading = analogRead(knockSensor);

  // print readings just to see what's going on
  if (debug && sensorReading > 0) {
    readCount++;
    if (readCount % 10 == 0) {
      Serial.println();
    }
    Serial.print(sensorReading);
    Serial.print("  ");
    // delay so serial not overloaded
    delay(50);
  }

  // if the sensor reading is greater than the threshold, 
  // and there's a bit of delay so we don't read single 
  // iPhone vibes as multiple:
  if (sensorReading >= threshold) {
    if (millis() - lastReadTime > 2500) {
      
      // update vibe count
      vibeCount++;  
    
      // toggle the status of the ledPin:
      ledState = !ledState;   
      // update the LED pin itself:        
      digitalWrite(ledPin, ledState);
  
      // show useful stuff on the computer
      Serial.println();
      Serial.print("Over Threashold: ");
      Serial.println(sensorReading);
      Serial.println("Readings...");
      // delay so serial not overloaded
      delay(50);
    }
    // update last read time
    lastReadTime = millis();
  }
}

void lcd_loop() {
  // display vibe count
  lcd.setCursor(12,0);
  lcd.print(vibeCount);

  // display elapsed time
  lcd.setCursor(6,1);
  lcd.print(time());
  delay(50);
}

String time() {
  unsigned long m = millis() - initTime;
  unsigned long secs = (m / 1000) % 60;
  unsigned long mins = (m / 1000 / 60) % 60;
  unsigned long hrs  = (m / 1000 / 60 / 60);

  String secsStr = String() + secs;
  if (secs < 10) {
     secsStr = String("0") + secs;
  }
  
  String minsStr = String() + mins;
  if (mins < 10) {
     minsStr = String("0") + mins;
  }
  
  return String() + hrs + ":" + minsStr + ":" + secsStr;
}

void loop() {
  lcd_loop();
  knock_loop();
}


