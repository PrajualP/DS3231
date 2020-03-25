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
}

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

}
