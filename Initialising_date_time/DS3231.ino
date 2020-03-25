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
//  set_display();
  /********Setting Alarm Time Contol Registers*************/
//  set_alarm_ctrl();
  /********Setting Alarm Time*************/
//  set_alarm();

  intial_digitalRead=digitalRead(7);
  
}

/***************************************First Set Alarm Time***************************************************************/
/*
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
   amorpm=0x60;//PM
  // amorpm=0x40;//AM
   seconds=20;
   minutes=2;
   hours=3;
   dates=24;
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
*/

/***************************************End of First Set Alarm Time****************************************************************/

/***************************************First Set Time****************************************************************/
/*
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
 amorpm=0x60;//PM
// amorpm=0x40;//AM
 seconds=30;
 minutes=35;
 hours=7;
 days=1;//Wednesday
 dates=4;
 months=11;
 years=19;

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
*/

/***************************************End of First Set Time****************************************************************/

/***************************************Display Time****************************************************************/

  uint8_t *read_register(uint8_t register_code, uint8_t no_of_bytes) {
    static uint8_t ret[7] = {0x00};
    Wire.beginTransmission(DEVICE_I2C_ADDRESS); // start transmission to device
    Wire.write(register_code); // sends register address to read from
    Wire.endTransmission(false); // end transmission
  
    Wire.requestFrom(DEVICE_I2C_ADDRESS, (uint8_t)no_of_bytes);// send data n-bytes read
    for (int i = 0; i < no_of_bytes; i++) {
      ret[i] = Wire.read(); // receive DATA
    }
  //  for (int i = 0; i < no_of_bytes; i++) {
  //    Serial.println(ret[i]);
  //  }
    return ret;
  }

void watch_display(){
  uint8_t *temp;
  temp= read_register(0x00, 7);
  Serial.println("*****************************");
 uint8_t seconds=(*temp&0x0F)+(((*temp&0x70)>>4)*10);
  temp++;
  uint8_t minutes=(*temp&0x0F)+(((*temp&0x70)>>4)*10);
  temp++;
  uint8_t hours = 0; 

//  Serial.print("Real Value: ");
//  Serial.println(*temp);
  
//  if((*temp&40)>>6){
//      Serial.println("12 hrs clock");
      Serial.print("Time: ");
      hours=((*temp&0x10)>>4)*10+(*temp&0x0F);
      Serial.print(hours);   
      Serial.print(":");
      
//  }
//  else{
//    Serial.print("24 hrs clock");
//    Serial.print("Time: ");
//    hours=((*temp&0x20)>>5)*20+((*temp&0x10)>>4)*10+(*temp&0x0F);
//    Serial.print(hours);   
//      Serial.print(":");
//  }
//  
  Serial.print(minutes);
  Serial.print(":");
  Serial.print(seconds);
  if((*temp&0x20)>>5){
    Serial.println("PM");
  }
   else{
    Serial.println("AM");
    }
  
  //Day
  temp++;
  uint8_t day_value=(*temp);
  Serial.print("Day:");
  char today[10];
  strcpy(today,daysofweek[day_value-1]);
  Serial.println(today);
  
  //Date
  temp++;
  Serial.print("Date:");
  uint8_t date_val=((*temp&0x30)>>4)*10+(*temp&0x0F);
  Serial.println(date_val);

  //Month
  temp++;
  Serial.print("Month:");
  uint8_t month_val=((*temp&0x10)>>4)*10+(*temp&0x0F);
  Serial.println(month_val);

   //Year
  temp++;
  Serial.print("Year:");
  uint8_t Year=(((*temp&0xF0)>>4)*10)+(*temp&0x0F);
  Serial.println(2000+Year);
  
  Serial.println("*****************************"); 
}



/***************************************End of Display Time****************************************************************/

void loop() {
  // put your main code here, to run repeatedly:
  
  watch_display();
  delay(2000);
//  if(digitalRead(7)!=intial_digitalRead){
//    Serial.println("Alarm Triggered");  
//  }
  
//  delay(20);
}
