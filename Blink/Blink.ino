// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 

Servo myservo[6];  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
int servoport[6]={6,7,8,9,10,11};
int pos = 0;    // variable to store the servo position 

void setup() 
{ 
  Serial.begin(9600);
   for (int i=0;i<6;i++)
   myservo[i].attach(servoport[i]);
} 


void loop() 
{ 
   Serial.println(myservo[0].read());
   for (int i=0;i<6;i++)
  if (i%2==0) {
  myservo[i].write(15);
  } else {
    myservo[i].write(179);
  }
  delay(3000);
 for (int i=16;i<180;i++)
 {
  for (int j=0;j<6;j++)
  if (j%2==0)
  myservo[j].write(i);
  else myservo[j].write(195-i);
  delay(15);
   Serial.println(myservo[0].read());
   
 }// attaches the servo on pin 9 to the servo object 
 for (int i=16;i<180;i++)
 {
  for (int j=0;j<6;j++)
  if (j%2==0)
  myservo[j].write(i);
  else myservo[j].write(195-i);
  delay(15);
   Serial.println(myservo[0].read());
   
 }
} 
