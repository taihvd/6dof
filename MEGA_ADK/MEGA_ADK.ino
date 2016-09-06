#include<Servo.h>

Servo myservo[6];
int servoport[6]={6,7,8,9,10,11};
int servomiddleplace[6]={90,90,90,90,90,90};
int uso;
int minservo=15,maxservo=165;
int a,b,c,d,e,f,selection;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  for (int i=0;i<6;i++)
  {
    myservo[i].attach(servoport[i]);
    myservo[i].write(servomiddleplace[i]);
    delay(1);
  }
  delay(1000);
}

void loop() {
  if (Serial.available()>0) {
    selection=Serial.parseInt();
    switch(selection)   {
      case 1: {     
        a=Serial.parseInt();
        a=constrain(a,15,180);
        myservo[0].write(a);
      }
      break;
      case 2: {
        b=Serial.parseInt();
        b=constrain(b,15,180);
        myservo[1].write(b); 
      }       
      break;
      case 3: {
        c=Serial.parseInt();
        c=constrain(c,15,180);
               myservo[2].write(c); break;
      }
      case 4:d=Serial.parseInt();
      d=constrain(d,15,180);
               myservo[3].write(d); break; 
      case 5: {
             e=Serial.parseInt();
             e=constrain(e,15,180);
               myservo[4].write(e); break;
      }
      case 6: f=Serial.parseInt();
      f=constrain(f,15,180);
               myservo[5].write(f); break;    
      case 9: 
        for (int i=0;i<6;i++) {
          myservo[i].write(90);
          delay(1);
        }
       break;
    }
  }
  delay(1);
//  myservo[0].write(minservo);
//  delay(2000);
//  myservo[0].write(maxservo);
//  delay(2000);
}
