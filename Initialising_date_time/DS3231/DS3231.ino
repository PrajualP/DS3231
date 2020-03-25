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
  /********Setting Actual Time*************/
  set_display();
  
}

/***************************************First Set Time****************************************************************/

void write_register_set_display(uint8_t register_code,uint8_t data[7]){
  Wire.beginTransmission(DEVICE_I2C_ADDRESS); // start transmission to device
  Wire.write(register_code); // sends register address to read from
  Wire.write(data[0]);
  Wire.write(data[1]);
  Wire.write(data[2]);
  Wire.write(data[3]);
  Wire.write(data[4]);
  Wire.write(data[5]);
  Wire.write(data[6]);
  Wire.endTransmission(false); // end transmission
}


void set_display(){
 uint8_t seconds,minutes,hours,days,dates,months,years,amorpm;
 /*Section to be enterred manually once*/
 
 amorpm=0x60;//PM
// amorpm=0x40;//AM
 seconds=30;
 minutes=35;
 hours=7;
 days=1;//monday
 dates=4;
 months=11;
 years=19;
 
 /*End of Manual Entry*/

 uint8_t data[7]={0x00};
  //Storing the passed seconds
  data[0]=(seconds/10)<<4|(seconds%10);
  //Storing the passed minutes
  data[1]=(minutes/10)<<4|(minutes%10);
  //Storing the passed hours
  data[2]=(hours/10)<<4|(hours%10);
  data[2]=data[2]|amorpm;
   //Storing the passed days
  data[3]=days;
  //Storing the passed dates
  data[4]=(dates/10)<<4|(dates%10);
  //Storing the passed months
  data[5]=(months/10)<<4|(months%10);
  //Storing the passed Year
  data[6]=(years/10)<<4|(years%10);
 write_register_set_display(0x00,data);
}

/***************************************End of First Set Time****************************************************************/



/***************************************End of Display Time****************************************************************/

void loop() {
  // put your main code here, to run repeatedly:
}
