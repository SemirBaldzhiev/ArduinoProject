#include <NewPing.h>
#include <Servo.h> 

#define E1  3    
#define E2  11   
#define M1  12            
#define M2  13


#define TRIG_PIN 7
#define ECHO_PIN 6 
#define MAX_DISTANCE 200 

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 
Servo myservo;   
int distance = 100;

void setup() {
  // put your setup code here, to run once:
  pinMode(M1,OUTPUT); 
  pinMode(M2,OUTPUT); 
  pinMode(E1,OUTPUT); 
  pinMode(E2,OUTPUT);  
  myservo.attach(10);  
  myservo.write(115); 
  delay(1000);
  distance = readPing();
  delay(100);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 int distanceR = 0;
 int distanceL =  0;
 delay(40);
 

   if(distance<=15)
   {
    moveStop();
    delay(100);
    moveBackward();
    delay(300);
    moveStop();
    delay(200);
    distanceR = lookRight();
    delay(300);
    distanceL = lookLeft();
    delay(300);
  

    if((distanceR <= 15) && (distanceL <= 15)){
     
      moveBackward();
      delay(2000);
    }
    else{  
      if(distanceR>=distanceL)
      {
        turnRight();
        delay(2000);
        //moveStop();
        
      }else
      {
        turnLeft();
        delay(2000);
        //moveStop();
      }
    }
   }else
   {
    moveForward();
   }
   distance = readPing();
   
}

void moveForward()     // move forward
{
    digitalWrite(M1,LOW);    
    digitalWrite(M2,LOW);  
    analogWrite(E1,150);   
    analogWrite(E2,150);
}
void turnRight()        // turn right 
{
   digitalWrite(M1,HIGH);  
   digitalWrite(M2,LOW); 
   analogWrite(E1,250);   
   analogWrite(E2, 250);
}
void turnLeft()        // turn left 
{
   digitalWrite(M1,LOW);   
   digitalWrite(M2, HIGH);   
   analogWrite(E1,150);   
   analogWrite(E2, 150);
}    
void moveStop()              // stop 
{
    digitalWrite(M1,LOW);    
    digitalWrite(M2, LOW);  
    analogWrite(E1, 0);   
    analogWrite(E2, 0);  // both left and right wheels stop
}
void moveBackward()            // move backward
{
   digitalWrite(M1,HIGH);   // both left and right wheels move backward
   digitalWrite(M2, HIGH);  
   analogWrite(E1,150);   
   analogWrite(E2, 150);
}

int lookRight()
{
    myservo.write(50); 
    delay(650);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    return distance;
}

int lookLeft()
{
   myservo.write(170); 
    delay(650);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    return distance;
    delay(100);
}

int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}
