/* YourDuino.com Electronic Bricks Set - Thermistor Analog-Digital
 See: http://yourduino.com/sunshop2/index.php?l=product_detail&p=364
 - ELECTRONIC BRICK: A Red brick with an LM393 comparator chip
   and both digital and analog outputs.
 - SEE the comments after "//" on each line below
 - CONNECTIONS:
   - 3-pin cable from Brick G-+-DO to RoboRED pin 3
   - added single wire from Brick AO to RoboRED A0
   - OnBoard Pin 13 LED
   - (Optional) Active Buzzer brick on Digital Pin 13
 - V1.01 03/26/2015
   Questions: terry@yourduino.com */

/*-----( Import needed libraries )-----*/
//NONE
/*-----( Declare Constants and Pin Numbers )-----*/
#define LED_PIN 13          // define on-board LED 
#define DIGITAL_IN_PIN  7   // define the digital input pin
#define ANALOG_IN_PIN   A0  // define the analog input pin

/*-----( Declare objects )-----*/
//NONE

/*-----( Declare Variables )-----*/
int    digitalValue ;  // read digital value
int    analogValue;    // read analog value
int    correctedAnalogValue;  // Value corrected for "Upside down" Thermistor
float  celciusTemperature;
float  fahrenheitTemperature;

void setup()   /****** SETUP: RUNS ONCE ******/
{
  pinMode (LED_PIN, OUTPUT) ;      // Onboard LED
  pinMode (DIGITAL_IN_PIN, INPUT) ;// digital input signal (Not actually required; INPUT is default)
  pinMode (ANALOG_IN_PIN, INPUT)  ;// analog  input signal (Not actually required; INPUT is default)
  Serial.begin(9600);              // Start the Serial Monitor connection
  Serial.println("YourDuino.com Electronic Brick Set: Thermistor Analog-Digital Brick Data:"); 
}//--(end setup )---


void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{
  
/*----------( Read the Analog data, do calculations )---------------------*/  
  analogValue = analogRead(ANALOG_IN_PIN);
  Serial.print("Analog value = ");
  Serial.print(analogValue), DEC; // display analog value
  
  // The Brick has the resistor-thermistor positions reversed from what the
  // "Thermistor" algorithm expects. "Fix It In Software" :-)
  correctedAnalogValue = map(analogValue, 0, 1023, 1023, 0);

  celciusTemperature    = Thermistor(correctedAnalogValue); // Calculate temperature 
  fahrenheitTemperature = (celciusTemperature * 9.0) / 5.0 + 32.0; // Convert Celcius to Fahrenheit  

/*----------( Read the Digital data, do calculations )---------------------*/
  digitalValue = digitalRead (DIGITAL_IN_PIN) ;
  Serial.print("   Digital value = ");
  Serial.println(digitalValue), DEC; // display digital value  
  Serial.print("High Temperature Switch = "); 
  if (digitalValue == HIGH) // When the sensor value exceeds the set point, LED/Buzzer is turned on
  {
    digitalWrite (LED_PIN, HIGH);
    Serial.print("ON ");
  }
  else
  {
    digitalWrite (LED_PIN, LOW);
    Serial.print("OFF ");    
  }


/*-----( Print out the calculated Temperatures )-----*/  
  Serial.print("Measured Temperature = ");
  Serial.print(fahrenheitTemperature, 1); // display Fahrenheit
  Serial.print(" F  ");
  Serial.print(celciusTemperature, 1); // display Celcius
  Serial.println(" C");  
  
  Serial.println(); // A blank line separator
  delay(1000);      // Wait a little
 
}//--(end main loop )---

/*-----( Declare User-written Functions )-----*/
// "Thermistor" function does a 3rd order formula to find the temperature from the voltage
// See http://en.wikipedia.org/wiki/Thermistor
double Thermistor(int RawADC) 
{
double Temp;  // Working variable
  Temp = log(((10240000 / RawADC) - 10000));
  Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp)); //Cube!
  Temp = Temp - 273.15;            // Convert Kelvin to Celcius
  return Temp;
}// END Thermistor Function

//*********( THE END )***********


