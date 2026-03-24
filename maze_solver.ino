// C++ code
/*
 * Maze Solving Robot - ELEC1601
 * 
 * Description:
 * Arduino-based autonomous robot that navigates a maze using IR sensors.
 * Detects obstacles (left, right, front) and makes decisions to move,
 * turn, or perform U-turns based on sensor input.
 * 
 * Features:
 * - IR-based distance detection using frequency sweeping
 * - Real-time navigation and obstacle avoidance
 * - Servo motor control for movement
 * 
 * Author: Your Name
 */
//
#include <Servo.h>
Servo servoLeft;
Servo servoRight;
int rightValue;
int leftValue;
int frontValue;
boolean rightDone;
boolean leftDone;
boolean nextRight = true;
boolean nextLeft = true;

void setup()
{
  pinMode(11, INPUT);
  pinMode(7, INPUT);
  pinMode(3, INPUT);
  pinMode(10, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(2, OUTPUT);
  Serial.begin(9600);
  servoLeft.attach(13);
  servoRight.attach(12);
  delay(1000);
  
}



int irDetect(int irLedPin, int irReceiverPin, long frequency)
{
  tone(irLedPin, frequency);                 // Turn on the IR LED square wave
  delay(1);                                  // Wait 1 ms
  int ir = digitalRead(irReceiverPin);       // IR receiver -> ir variable
  noTone(irLedPin);                          // Turn off the IR LED
  delay(1);                                  // Down time before recheck
  return ir;                                 // Return 0 detect, 1 no detect
}

int irDistanceLeft(int irLedPin, int irReceiverPin)
{
   int distance = 0;
   for(long f = 38000; f <= 42000; f += 1000)
   {
      distance += irDetect(irLedPin, irReceiverPin, f);
   }
   return distance;
}

int irDistanceRight(int irLedPin, int irReceiverPin)
{
   int distance = 0;
   for(long f = 37800; f <= 42000; f += 1000)
   {
      distance += irDetect(irLedPin, irReceiverPin, f);
   }
   return distance;
}

int irDistanceFront(int irLedPin, int irReceiverPin)
{
   int distance = 0;
   for(long f = 38000; f <= 42000; f += 1000)
   {
      distance += irDetect(irLedPin, irReceiverPin, f);
   }
   return distance;
}

void right90(){
  servoLeft.writeMicroseconds(1550);
  servoRight.writeMicroseconds(1550);
  delay(700);
}

void left90(){
  servoLeft.writeMicroseconds(1450);
  servoRight.writeMicroseconds(1450);
  delay(900);
}

void adjustRight(){
  servoLeft.writeMicroseconds(1750);
  servoRight.writeMicroseconds(1438);
  delay(75);
}

void adjustLeft(){
  servoLeft.writeMicroseconds(1547);
  servoRight.writeMicroseconds(1250);
  delay(85);
}

void uturn(){
  servoLeft.writeMicroseconds(1550);
  servoRight.writeMicroseconds(1550);
  delay(1500);
}

void loop()
{
  rightValue = irDistanceRight(2, 3);
  leftValue = irDistanceLeft(10, 11);
  frontValue = irDistanceFront(6, 7);

  
  
  Serial.print("Right: ");
  Serial.println(rightValue);
  Serial.println("");
  Serial.print("Left: ");
  Serial.println(leftValue);
  Serial.println("");
  Serial.print("Front: ");
  Serial.println(frontValue);

  servoLeft.writeMicroseconds(1547);
  servoRight.writeMicroseconds(1438);
  delay(25);

// adjust right
  if (leftValue <= 1 && rightValue >= 2){
    adjustRight();
  }

// adjust left
  else if (leftValue >= 2 && rightValue == 0){
    adjustLeft();
  }
  
    // u turn
  else if (frontValue < 4 && leftValue <= 2 && rightValue <= 3){
    if (rightDone){
      uturn();
      nextLeft = false;
    }
    else if (leftDone){
      uturn();
      nextRight = false;
    }
  }

// right 90
  else if (rightValue > 2 && leftValue <= 2){
    if (nextRight){
      right90();
      rightDone = true;
      leftDone = false;
    }
    else{
      delay(1500); // to skip one block length
      nextRight = true;
    }
  }

// left 90
  else if (leftValue > 4 && rightValue <= 3){
    if (nextLeft){
      left90();
      leftDone = true;
      rightDone = false;
    }
    else{
      delay(1500);
      nextLeft = true;
    }
      
  }

// adjust left
  else if (leftValue >= 2 && rightValue == 0){
    adjustLeft();
  }


}
