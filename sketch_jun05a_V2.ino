#include <Servo.h>
Servo servo;

int buzzer = 2;
int servoPin = 3;

int echoFront = 5;
int triggerFront = 7;
int echoRight = 8;
int triggerRight = 9;
int echoLeft = 12;
int triggerLeft = 13;
                                                                                                                                                                                                                                                                                                                            
int distLeft = 0;
int distRight = 0;
int distFront = 0;
long time=0;
int maxDist = 80; // detect objects 80cm or closer

void setup() {
  Serial.begin(9600);
  pinMode(triggerFront, OUTPUT);
  pinMode(echoFront, INPUT);
  pinMode(triggerLeft, OUTPUT);
  pinMode(echoLeft, INPUT);
  pinMode(triggerRight, OUTPUT);
  pinMode(echoRight, INPUT);
  pinMode(buzzer, OUTPUT);
  servo.attach(servoPin); 
  servo.write(90);
}

void loop() {
  digitalWrite(buzzer, LOW);
  
  Pulse(triggerLeft, echoLeft);
  distLeft = time * 0.017; 	// convert to cm
  Pulse(triggerRight, echoRight);
  distRight = time * 0.017;	// convert to cm
  Pulse(triggerFront, echoFront);
  distFront = time * 0.017;	// convert to cm
  
  if (distFront <= maxDist){
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
  }
  if (distLeft <= maxDist){
    servo.write(0);
    delay(500);
  }
  else if (distRight <= maxDist){
    servo.write(180);
    delay(500);
  }
  servo.write(90);
  delay(250);
  digitalWrite(buzzer, LOW);
}


void Pulse(int trig, int echo){
  digitalWrite(trig, LOW);
  delay(5);
  digitalWrite(trig, HIGH);
  delay(10);
  digitalWrite(trig, LOW);
  time = pulseIn(echo, HIGH);
}
