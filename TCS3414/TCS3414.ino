// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// TCS3414
// This code is designed to work with the TCS3414_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Color?sku=TCS3414_I2CS#tabs-0-product_tabset-2

#include <Wire.h>

// TCS3414 I2C address is 0x39(57)
#define Addr 0x39

void setup()
{
  // Initialise I2C communication as MASTER
  Wire.begin();
  // Initialise serial communication, set baud rate = 9600
  Serial.begin(115200);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select control register with command register, 0x80(128)
  Wire.write(0x00 | 0x80);
  // ADC enable, Power On
  Wire.write(0x03);
  // Stop I2C transmission
  Wire.endTransmission();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select gain register with command register, 0x80(128)
  Wire.write(0x07 | 0x80);
  // Gain = 1x, Prescaler Mode = Divide by 1
  Wire.write(0x00);
  // Stop I2C transmission
  Wire.endTransmission();
  delay(300);
}

void loop()
{
  unsigned int data[8];

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select data register with command register, 0x80(128)
  Wire.write(0x10 | 0x80);
  // Stop I2C transmission
  Wire.endTransmission();

  // Request 8 bytes of data
  Wire.requestFrom(Addr, 8);

  // Read the 8 bytes of data
  // green lsb, green msb, red lsb, red msb
  // blue lsb, blue msb, cData lsb, cData msb
  if (Wire.available() == 8)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
    data[3] = Wire.read();
    data[4] = Wire.read();
    data[5] = Wire.read();
    data[6] = Wire.read();
    data[7] = Wire.read();
  }

  // Convert the data
  float green = data[1] * 256.0 + data[0];
  float red = data[3] * 256.0 + data[2];
  float blue = data[5] * 256.0 + data[4];
  float cData = data[6] * 256.0 + data[5];

  float max = green;
  if (red > max) max = red;
  if (blue > max) max = blue;
  
    red=100.0*red/max;
    green=100.0*green/max;
    blue=100.0*blue/max;
  

  // Calculate luminance
  float luminance = (-0.32466 * red) + (1.57837 * green) + (-0.73191 * blue);

  // Output data to serial monitor
  Serial.print("Red : ");
  Serial.print(red)  ;
  Serial.print(" Green : ");
  Serial.print(green);
  Serial.print(" Blue : ");
  Serial.println(blue) ;
  //  Serial.print("Clear Data Luminance : ");
  //  Serial.println(cData) ;
  //  Serial.print("Ambient Light Luminance : ");
  //  Serial.println(luminance);
  delay(500);
}
