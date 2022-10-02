
#include <Wire.h>
int CMD_DELAY = 10;
void setup() {
  while(!Serial);
  delay(100);
  int msg = 1;
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(115200);  // start serial for output
  Wire.beginTransmission(0x55); //cofigure output
  Wire.write(0x10);
  Wire.write(0x00);
  Wire.write(0x01);
  Wire.endTransmission();
     delay(CMD_DELAY);
  Wire.requestFrom(0x55, 1);

  msg = Wire.read();
  Serial.print("outputmodeconfig: ");
  Serial.println(msg);
   delay(CMD_DELAY);
  
   Wire.beginTransmission(0x55); //cofigure FIFO to 1 at a time 
  Wire.write(0x10);
  Wire.write(0x01);
  Wire.write(0x01);
  Wire.endTransmission();
  Wire.requestFrom(0x55, 1);
   delay(CMD_DELAY);
  msg = Wire.read();
  Serial.print("outputmodeconfig: ");
  Serial.println(msg);
  
    Wire.beginTransmission(0x55); //cofigure sensor enable 
  Wire.write(0x44);
  Wire.write(0x00);
  Wire.write(0x01);
  Wire.write(0x00);
  Wire.endTransmission();
  delay(100);
  Wire.requestFrom(0x55, 1);
    //extra delay to enable 
  msg = Wire.read();
  Serial.print("sensorreadyconfig: ");
  Serial.println(msg); 
      Wire.beginTransmission(0x55); //cofigure imu enable 
  Wire.write(0x44);
  Wire.write(0x04);
  Wire.write(0x01);
  Wire.write(0x01);
  Wire.endTransmission();
  delay(100);
  Wire.requestFrom(0x55, 1);
    //extra delay to enable 
  msg = Wire.read();
  Serial.print("imuconfig: ");
  Serial.println(msg); 

  Wire.beginTransmission(0x55); //wrist HR monitor algorithm 
  Wire.write(0x52);
  Wire.write(0x02);
  Wire.write(0x01); //disable 
  Wire.endTransmission();
  delay(1000);
  Wire.requestFrom(0x55, 1);
  msg = Wire.read();
  Serial.print("HRalgoconfig: ");
  Serial.println(msg);
  delay(100);
  Wire.beginTransmission(0x55); //read status
  Wire.write(0x00);
  Wire.write(0x00); 
  Wire.endTransmission();
  delay(CMD_DELAY);
  Wire.requestFrom(0x55, 1);
  msg = Wire.read();
  Serial.print("error: ");
  Serial.println(msg);
  msg = Wire.read();
  Serial.print("status:");
  Serial.println(msg);
  
  


  
}

void loop() {
      // Information from the readBpm function will be saved to our "body"
    // variable.  
    int msg;
      Wire.beginTransmission(0x55); //get sasmples 
  Wire.write(0x12);
  Wire.write(0x00); 
  Wire.endTransmission();
  delay(CMD_DELAY);
  Wire.requestFrom(0x55, 2); 
  msg = Wire.read();
  Serial.print("error: ");
  Serial.println(msg);
  msg = Wire.read();
  Serial.print("sample:");
  Serial.println(msg);
  
     Wire.beginTransmission(0x55); //wrist HR monitor algorithm 
  Wire.write(0x12);
  Wire.write(0x00); 
  Wire.endTransmission();
  delay(CMD_DELAY);
  Wire.requestFrom(0x55, 26);
  while (Wire.available()) { // slave may send less than requested
    int c = Wire.read(); // receive a byte as character
    Serial.print(c);         // print the character
  }
    delay(2000);
    Serial.println();


}
