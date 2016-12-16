/*
  Reading a serial ASCII-encoded string.

 This sketch demonstrates the Serial parseInt() function.
 It looks for an ASCII string of comma-separated values.
 It parses them into ints, and uses those to fade an RGB LED.

 Circuit: Common-Cathode RGB LED wired like so:
 * Red anode: digital pin 3
 * Green anode: digital pin 5
 * Blue anode: digital pin 6
 * Cathode : GND

 created 13 Apr 2012
 by Tom Igoe
 
 modified 14 Mar 2016
 by Arturo Guadalupi

 This example code is in the public domain.
 */
//GND goes to +5v
// pins for the LEDs:
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

int red = 0;
int green = 0;
int blue = 0;


void setup() {
  // initialize serial:
  Serial.begin(9600);
  // make the pins outputs:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

}

void loop() {

      delay(10);
      if(red < 255){
        red += 1;
      }else if(green < 255){
        green += 1;
      }else if(blue < 255){
        blue += 1;
      }else{
        red = 0;
        green = 0;
        blue = 0;
      }

      
      // constrain the values to 0 - 255 and invert
      // if you're using a common-cathode LED, just use "constrain(color, 0, 255);"
      int redColor = 255 - constrain(red, 0, 255);
      int greenColor = 255 - constrain(green, 0, 255);
      int blueColor = 255 - constrain(blue, 0, 255);

      // fade the red, green, and blue legs of the LED:
      analogWrite(redPin, redColor);
      analogWrite(greenPin, greenColor);
      analogWrite(bluePin, blueColor);

      // print the three numbers in one string as hexadecimal:
      Serial.print(red, DEC);
      Serial.print(green, DEC);
      Serial.println(blue, DEC);
    

}