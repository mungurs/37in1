// Henry's Bench
// KY-008 Tutorial... On then Off


int laserPin = 10;

void setup ()
{
   pinMode (laserPin, OUTPUT); // define the digital output interface 13 feet
}
void loop () {
   digitalWrite (laserPin, HIGH); // Turn Laser On
   delay (50); // On For Half a Second
   digitalWrite (laserPin, LOW); // Turn Laser Off
   delay (50); // Off for half a second
}


