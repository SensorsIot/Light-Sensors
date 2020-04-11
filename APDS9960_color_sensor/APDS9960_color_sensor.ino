/***************************************************************************
  This is a library for the APDS9960 digital proximity, ambient light, RGB, and gesture sensor

  This sketch puts the sensor in color mode and reads the RGB and clear values.

  Designed specifically to work with the Adafruit APDS9960 breakout
  ----> http://www.adafruit.com/products/3595

  These sensors use I2C to communicate. The device's I2C address is 0x39

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Dean Miller for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include "Adafruit_APDS9960.h"
Adafruit_APDS9960 apds;

void setup() {
  Serial.begin(115200);

  if(!apds.begin()){
    Serial.println("failed to initialize device! Please check your wiring.");
  }
  else Serial.println("Device initialized!");

  //enable color sensign mode
  apds.enableColor(true);
}

void loop() {
  //create some variables to store the color data in
  uint16_t r, g, b, c;
  
  //wait for color data to be ready
  while(!apds.colorDataReady()){
    delay(5);
  }

  //get the data and print the different channels
  apds.getColorData(&r, &g, &b, &c);

   float green = (float)g;
  float red = (float)r;
  float blue = (float)b;

  float max = green;
  if (red > max) max = red;
  if (blue > max) max = blue;

  red = 100.0 * red / max;
  green = 100.0 * green / max;
  blue = 100.0 * blue / max;

  Serial.print(" Red : ");
  Serial.print(red)  ;
  Serial.print(" Green : ");
  Serial.print(green);
  Serial.print(" Blue : ");
  Serial.println(blue) ;
  
  delay(500);
}
