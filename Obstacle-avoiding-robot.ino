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

int distance;
int distanceR;
int distanceL;

void setup() {
  // put your setup code here, to run once:
  pinMode(M1,OUTPUT); 
  pinMode(M2,OUTPUT); 
  pinMode(E1,OUTPUT); 
  pinMode(E2,OUTPUT);  
  myservo.attach(10);  
  myservo.write(90); 
  delay(300);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 myservo.write(90); 
 distance = readPing();
 
 if(distance<=22)
 {
        moveStop();
        delay(300);
        distanceR = lookRight();
        delay(300);
        distanceL = lookLeft();
        delay(300);
        if((distanceL<=25)&&(distanceR<=25)){
           moveBackward(200);
           delay(3000);
          }
          else
          {
             if(distanceR>=distanceL)
              {
                turnRight();
                delay(1000); 
              }
              else 
              {
                turnLeft();
                delay(1000); 
              }
          }
 }
 else 
 {
   moveForward();
   delay(1000);
 }
}
void moveForward()     // move forward
{
    digitalWrite(M1,LOW);    
    digitalWrite(M2,LOW);  
    analogWrite(E1,120);   
    analogWrite(E2,120); 
}
void turnRight()        // turn right 
{
   
   digitalWrite(M1,HIGH);  
   digitalWrite(M2,LOW); 
   analogWrite(E1,220);   
   analogWrite(E2, 220);
}
void turnLeft()        // turn left 
{
   
   digitalWrite(M1,LOW);   
   digitalWrite(M2, HIGH);   
   analogWrite(E1,220);   
   analogWrite(E2, 220);
}    
void moveStop()              // stop 
{
    digitalWrite(M1,LOW);    
    digitalWrite(M2, LOW);  
    analogWrite(E1, 0);   
    analogWrite(E2, 0);  // both left and right wheels stop
}
void moveBackward(int speedBack)            // move backward
{
   
   digitalWrite(M1,HIGH);   // both left and right wheels move backward
   digitalWrite(M2, HIGH);  
   analogWrite(E1,speedBack);   
   analogWrite(E2, speedBack);
}

int lookRight()
{
    myservo.write(10); 
    delay(650);
    int distance = readPing();
    delay(100);
    myservo.write(90); 
    return distance;
}

int lookLeft()
{
   myservo.write(170); 
    delay(650);
    int distance = readPing();
    delay(100);
    myservo.write(90); 
    return distance;  
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
