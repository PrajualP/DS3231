#include <Wire.h>
#include <string.h>
#define DEVICE_I2C_ADDRESS 0x68
char daysofweek[8][10]={"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};
int intial_digitalRead =0;
void setup()
{
  uint16_t ret;
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  pinMode(7, INPUT);
  Serial.println("\nDS3231");
  /********Setting Alarm Time Contol Registers*************/
  set_alarm_ctrl();
  /********Setting Alarm Time*************/
  set_alarm();

  intial_digitalRead=digitalRead(7);
  
}

/***************************************First Set Alarm Time***************************************************************/

void set_alarm_ctrl(){
  //Resetting the Control Register First
  Wire.beginTransmission(DEVICE_I2C_ADDRESS); // start transmission to device
  Wire.write(0x0F); // sends register address
  Wire.write(0x88);
  Wire.endTransmission(false); // end transmission 
  delay(100);
  //Changing the control Registers
  Wire.beginTransmission(DEVICE_I2C_ADDRESS); // start transmission to device
  Wire.write(0x0E); // sends register address
  Wire.write(0x1D);
  Wire.endTransmission(false); // end transmission  

  Wire.beginTransmission(DEVICE_I2C_ADDRESS); // start transmission to device
  Wire.write(0x0E); // sends register address
  Wire.endTransmission(false); // end transmission
  Wire.requestFrom(DEVICE_I2C_ADDRESS, (uint8_t)1);
  uint8_t value=Wire.read();
  Serial.print("The Control Reg Value Now is:");
  Serial.println(value);
}

void set_alarm(){
  //Setting Alarm 1
  uint8_t seconds,minutes,hours,days,dates,months,years,amorpm;

  /*Manual Entry Section*/
   amorpm=0x60;//PM
  // amorpm=0x40;//AM
   seconds=20;
   minutes=2;
   hours=3;
   dates=24;
  /*End of Manual Entry Section*/
  
  uint8_t data[5]={0x00};
    //Storing the passed seconds
  data[0]=(seconds/10)<<4|(seconds%10);
  //Storing the passed minutes
  data[1]=(minutes/10)<<4|(minutes%10);
  //Storing the passed hours
  data[2]=(hours/10)<<4|(hours%10);
  data[2]=data[2]|amorpm;
  //Storing the passed dates
  data[3]=(dates/10)<<4|(dates%10);
  data[3]=data[3]&0x3F;
  Wire.beginTransmission(DEVICE_I2C_ADDRESS); // start transmission to device
  Wire.write(0x07); // sends register address to read from
  Wire.write(data[0]);
  Wire.write(data[1]);
  Wire.write(data[2]);
  Wire.write(data[3]);
  Wire.endTransmission(false); // end transmission
}

/***************************************End of First Set Alarm Time****************************************************************/



void loop() {
  // put your main code here, to run repeatedly:
  /* Connect the alarm Interrruppt pin to Pin 7*/
  if(digitalRead(7)!=intial_digitalRead){
    Serial.println("Alarm Triggered");  
  }
 
}
