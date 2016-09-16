#include<Servo.h>

Servo myservo[6];
int servoport[6]={6,7,8,9,10,11};
int servomiddleplace[6]={100,110,105,100,90,100};
int uso;
int minservo=15,maxservo=175;
int type;
int serialGo[6];
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  for (int i=0;i<6;i++)
  {
    myservo[i].attach(servoport[i]);
    myservo[i].write(100);
    delay(1);
  }
  delay(1000);
}

void loop() {
  if (Serial.available()>0) {
       type=Serial.parseInt();
       type= constrain(type,0,6);
       uso=Serial.parseInt();
       uso=constrain(uso,minservo,maxservo);
       if (type!=6) myservo[type].write(uso);
       else for (int i=0;i<6;i++)
       {
        myservo[i].write(servomiddleplace[i]);
        delay(1);
       }
  }
}
