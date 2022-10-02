
#include <Wire.h>
int CMD_DELAY = 10;
int stat;
int msg;
int a1;
int a2;
int a3;
byte c;
unsigned long combined;
void setup() {
  delay(6);
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
   delay(CMD_DELAY);
  
   Wire.beginTransmission(0x55); //cofigure interupt threshold
  Wire.write(0x10);
  Wire.write(0x01);
  Wire.write(0x01);
  Wire.endTransmission();
  Wire.requestFrom(0x55, 1);
   delay(CMD_DELAY);
  msg = Wire.read();
  
    Wire.beginTransmission(0x55); //cofigure accel 
  Wire.write(0x44);
  Wire.write(0x04);
  Wire.write(0x01);
  Wire.write(0x00);
  Wire.endTransmission();
  delay(100);
  Wire.requestFrom(0x55, 1);
    //extra delay to enable 
  msg = Wire.read();
      Wire.beginTransmission(0x55); //cofigure sense
  Wire.write(0x44);
  Wire.write(0x00);
  Wire.write(0x01);   
  Wire.endTransmission();
  delay(100);
  Wire.requestFrom(0x55, 1);
    //extra delay to enable 
  msg = Wire.read();
  
  Wire.beginTransmission(0x55); //cofigure SR
  Wire.write(0x40);
  Wire.write(0x00);
  Wire.write(0x12);
  Wire.write(0x18);
  Wire.endTransmission();
  delay(CMD_DELAY);
  Wire.requestFrom(0x55, 1);
    //extra delay to enable 
  msg = Wire.read();
  
    Wire.beginTransmission(0x55); //cofigure LED1
  Wire.write(0x40);
  Wire.write(0x00);
  Wire.write(0x23);
  Wire.write(0xDF);
  Wire.endTransmission();
  delay(CMD_DELAY);
  Wire.requestFrom(0x55, 1);
  msg = Wire.read();
  
      Wire.beginTransmission(0x55); //cofigure LED2
  Wire.write(0x40);
  Wire.write(0x00);
  Wire.write(0x24);
  Wire.write(0xDF);
  Wire.endTransmission();
  delay(CMD_DELAY);
  Wire.requestFrom(0x55, 1);
    //extra delay to enable 
  msg = Wire.read();

        Wire.beginTransmission(0x55); //cofigure LED2
  Wire.write(0x40);
  Wire.write(0x00);
  Wire.write(0x25);
  Wire.write(0xDF);
  Wire.endTransmission();
  delay(CMD_DELAY);
  Wire.requestFrom(0x55, 1);

  msg = Wire.read(); 
  
  

  delay(4000);
  Wire.beginTransmission(0x55); //read status
  Wire.write(0x00);
  Wire.write(0x00); 
  Wire.endTransmission();
  delay(CMD_DELAY);
  Wire.requestFrom(0x55, 1);
  msg = Wire.read();
  msg = Wire.read();
  
  


  
}

void loop() {
      // Information from the readBpm function will be saved to our "body"
    // variable.  

      Wire.beginTransmission(0x55); //get sasmples 
  Wire.write(0x12);
  Wire.write(0x00); 
  Wire.endTransmission();
  Wire.requestFrom(0x55, 2);
  status = Wire.read();
  if (status == 0) {
  msg = Wire.read();
    if(msg > 0) {
      Wire.beginTransmission(0x55); 
      Wire.write(0x12);
      Wire.write(0x01); 
      Wire.endTransmission();
      Wire.requestFrom(0x55, 25);
      while (Wire.available()) { // slave may send less than requested
        //int track = Wire.available(); 
        
        //Serial.print(track);
        //Serial.print(":");
        c = Wire.read();
        if (Wire.available() == 24) {
          a3 = c;
        }
        else if (Wire.available() == 23) {
          a2 = c;
        }
        else if (Wire.available() == 22) {
          a1 = c;
        }
    }
      combined = 0; // clear it out
      combined = (a3<<16) | (a2<<8) | (a1);
      Serial.println(combined);
    }
  }
       

}
