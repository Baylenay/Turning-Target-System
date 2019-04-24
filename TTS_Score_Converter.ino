#include <SevSeg.h>
SevSeg sevseg; //Instantiate a seven segment controller object
float pressLength_milliSeconds = 0;
// Define the *minimum* length of time, in milli-seconds,
//that the button must be pressed for a particular option to occur
int optionOne_milliSeconds =  100;
int optionTwo_milliSeconds = 1000;
const int scrCh1           =   A0;
const int scrCh2           =   A1;
const int scrCh3           =   A2;
const int MotorButton      =   A3;
const int motorCh1         =   A4;
const int motorCh2         =   A5;
int scrCh1State            =    0;
int scrCh2State            =    0;
int scrCh3State            =    0;
int count;
int shots;


void setup() {
  pinMode     (scrCh1, INPUT);
  pinMode     (scrCh2, INPUT);
  pinMode     (scrCh3, INPUT);
  pinMode(MotorButton, INPUT);  
  byte        numDigits = 4;
  byte        digitPins[] = {2, 3, 4, 5};
  byte        segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);
  sevseg.setBrightness(2.75);
  int count = 0;            //this number represents the total score at any given point in time
  int shots = 0;            //this number represents the number of shots that have been taken
  

}

void loop() {
  scrCh1State =   digitalRead  (scrCh1);
  scrCh2State =   digitalRead  (scrCh2);
  scrCh3State =   digitalRead  (scrCh3);


if (scrCh1State ==  HIGH  ||  scrCh2State ==  HIGH  ||  scrCh3State ==  HIGH){
  
  if  (shots = 10){   //If a total of 10 shots have been taken, count and shots are reset in 
  count = 0;          //preperation for the routine to be repeated
  shots = 0;
  }
  delay(500);         //Once any channel is sent high it will stay high for 1s therefore,
                      //a delay of 0.5s provides enough time to make sure that, when tested,
                      //all possible channels are high.


//   _Ch1_|_Ch2_|_Ch3_
//  |_ 0 _|_ 0 _|_ 0 _|   -
//  |_ 0_ |_ 0 _|_ 1 _| = scr1
//  |_ 0_ |_ 1 _|_ 0 _| = scr2
//  |_ 0 _|_ 1 _|_ 1 _| = scr3
//  |_ 1 _|_ 0 _|_ 0 _| = scr4
//  |_ 1 _|_ 0 _|_ 1 _| = scr5
//  |_ 1 _|_ 1 _|_ 0 _|   -
//  |_ 1 _|_ 1 _|_ 1 _|   -

  
 
if (scrCh1State ==  LOW && scrCh2State ==  LOW  && scrCh3State ==  HIGH ){
  scr1(); 
}

if (scrCh1State ==  LOW && scrCh2State ==  HIGH  && scrCh3State ==  LOW ){
  scr2();
}

if (scrCh1State ==  LOW && scrCh2State ==  HIGH  && scrCh3State ==  HIGH ){
  scr3();
}

if (scrCh1State ==  HIGH && scrCh2State ==  LOW  && scrCh3State ==  LOW ){
  scr4();
}

if (scrCh1State ==  HIGH && scrCh2State ==  LOW  && scrCh3State ==  HIGH ){
  scr5();
}

}
while (digitalRead(MotorButton) == HIGH ){ //if motor button is pressed (0.15s) target is turned to
                                     //face and if motor button is held down for longer than
                                     //1.15s target is turned to side

    delay(50);  //for more resolution, lower this number 
    pressLength_milliSeconds = pressLength_milliSeconds + 100;   

}

  //Option 2 - Execute the second option if the button is held for the correct amount of time
  if (pressLength_milliSeconds >= optionTwo_milliSeconds){
    motorF();  
} 

  //option 1 - Execute the first option if the button is held for the correct amount of time
  else if(pressLength_milliSeconds >= optionOne_milliSeconds){
    motorS();  
}
  //every time through the loop, we need to reset the pressLength_Seconds counter
  pressLength_milliSeconds = 0;
}


// subroutine for diplaying score + total score 
void scr1() {
  for(int d =  0;d < 2000;d++) {
    sevseg.setNumber(100,0);
    sevseg.refreshDisplay();
  }
  count += 100;
  shots +=  1;
    for(int d =  0;d < 2000;d++) {
    sevseg.setNumber(count,0);
    sevseg.refreshDisplay();
  }
  return;
  } 

void scr2() {
  for(int d =  0;d < 2000;d++) {
    sevseg.setNumber(80,0);
    sevseg.refreshDisplay();
  }
  count +=  80;
  shots +=  1;
    for(int d =  0;d < 2000;d++) {
    sevseg.setNumber(count,0);
    sevseg.refreshDisplay();
  }
  return;
  }

void scr3() {
  for(int d =  0;d < 2000;d++) {
    sevseg.setNumber(60,0);
    sevseg.refreshDisplay();
  }
  count +=  60;
  shots +=  1;
    for(int d =  0;d < 2000;d++) {
    sevseg.setNumber(count,0);
    sevseg.refreshDisplay();
  }
  return;
  }
  
void scr4() {
  for(int d =  0;d < 2000;d++) {
    sevseg.setNumber(40,0);
    sevseg.refreshDisplay();
  }
  count +=  40;
  shots +=  1;
    for(int d =  0;d < 2000;d++) {
    sevseg.setNumber(count,0);
    sevseg.refreshDisplay();
  }
  return;
  }

void scr5() {
  for(int d =  0;d < 2000;d++) {
    sevseg.setNumber(20,0);
    sevseg.refreshDisplay();
  }
  count +=  20;
  shots +=  1;
    for(int d =  0;d < 2000;d++) {
    sevseg.setNumber(count,0);
    sevseg.refreshDisplay();
  }
  return;
  }

  // subroutine for turning target to face position
void motorF() {
  digitalWrite (motorCh1, HIGH);
  delay(500);
  digitalWrite  (motorCh1, LOW);
  return;
}

// subroutine for turning motor to side position
void motorS() {
  digitalWrite (motorCh2, HIGH);
  delay                   (500);
  digitalWrite  (motorCh2, LOW);
  return;
}

