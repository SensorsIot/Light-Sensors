
#define S0 4
#define S1 5
#define S2 2
#define S3 27
#define sensorIn 14
float frequency = 0;

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorIn, INPUT);

  // Setting frequency-scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  Serial.begin(115200);
}
void loop() {

  float red = measure(0, 0);
  float green =  measure(1, 1);
  float blue =  measure(0, 1);
  float white = measure(1, 0);

  float max = red;
  if (green > max) max = green;
  if (blue > max) max = blue;

  red = 100.0 * red / max;
  green = 100.0 * green / max;
  blue = 100.0 * blue / max;

  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(red);//printing RED color frequency
  Serial.print("  ");
  // Reading the output frequency
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(green);//printing RED color frequency
  Serial.print("  ");
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(blue);//printing RED color frequency
  // Printing the value on the serial monitor
  Serial.print("  ");
  Serial.print("C= ");//printing name  Serial.print(white);//printing RED color frequency
  Serial.print(white);//printing clear color frequency
  Serial.println("  ");

  delay(1000);
}

float measure(int s2_value, int s3_value) {
  digitalWrite(S2, s2_value);
  digitalWrite(S3, s3_value);
  // Reading the output frequency
  frequency = 10000.0 / pulseIn(sensorIn, LOW);
  return frequency;
}
