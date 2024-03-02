// Navigation Correction
// Programmer: Rob Garner (rgarner011235@gmail.com)
// Date: 1 Mar 2024
// Purpose: to create a compas and proximity detector for the makerblock mbot robot using the feather sense
// This code is adapted from a Feather Sense demo provided by Rianne Trujillo 
// that is similar to demo code found on the Ardufruit Feather Sense website here: 
// https://learn.adafruit.com/adafruit-feather-sense/overview?gad_source=1&gclid=CjwKCAiAloavBhBOEiwAbtAJO-r4-JhJr-W7oVUYgzrPXwQvS26WFnR3ia_3okDzJiHZqxSh7g3ctBoCPWEQAvD_BwE

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LIS3MDL.h>
#include <Adafruit_APDS9960.h> 

//Instantiate our sensor classes
Adafruit_APDS9960 apds9960; // proximity, gesture
Adafruit_LIS3MDL lis3mdl;  

//Variables to store sensor values
float magnetic_x, magnetic_y, magnetic_z;
uint8_t proximity;

void setup(void) 
{
  Serial.begin(115200);
  Serial.println("Magnetometer Test"); Serial.println("");
  
  // initialize the sensors
  apds9960.begin();
  apds9960.enableProximity(true);
  lis3mdl.begin_I2C();
}

void loop(void) 
{
    //get promimity/gesture readings
  proximity = apds9960.readProximity();

  /* Get a new sensor event */ 
  // sensors_event_t event; 
  // mag.getEvent(&event);
  //get magnetometer readings
  lis3mdl.read();
  magnetic_x = lis3mdl.x;
  magnetic_y = lis3mdl.y;
  magnetic_z = lis3mdl.z;

  float Pi = 3.14159;
  
  // Calculate the angle of the vector y,x
  float heading = (atan2(magnetic_z,magnetic_y) * 180) / Pi;
  
  // Normalize to 0-360
  if (heading < 0)
  {
    heading = 360 + heading;
  }
  //Output data as comma seperated values with heading first and proximity second.
  Serial.print(heading);
  Serial.print(", ");
  Serial.println(proximity);
  delay(500);
}