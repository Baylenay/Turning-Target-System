const int switch1    = A0;
const int switch2    = A1;
const int switch3    = A2;
const int switch4    = A3;
const int switch5    = A4;
const int motorCh1    = 2;
const int motorCh2    = 3;
const int scrCh1      = 4;
const int scrCh2      = 5;
const int scrCh3      = 6;
const int A           = 7;
const int B           = 8;
const int C           = 9;
const int D           =10;
const int enable      =11;
int switch1State      = 0;
int switch2State      = 0;
int switch3State      = 0;
int switch4State      = 0;
int switch5State      = 0;
int lastSwitch1State  = 0;
int lastSwitch2State  = 0;
int lastSwitch3State  = 0;
int lastSwitch4State  = 0;
int lastSwitch5State  = 0;
int motorCh1State     = 0;
int motorCh2State     = 0;
int switchScore;
int x;
int t;


void setup() {
  pinMode   (switch1, INPUT);
  pinMode   (switch2, INPUT);
  pinMode   (switch3, INPUT);
  pinMode   (switch4, INPUT);
  pinMode   (switch5, INPUT);
  pinMode  (motorCh1, INPUT);
  pinMode  (motorCh2, INPUT);
  pinMode   (scrCh1, OUTPUT);
  pinMode   (scrCh2, OUTPUT);
  pinMode   (scrCh3, OUTPUT);
  pinMode        (A, OUTPUT);
  pinMode        (B, OUTPUT);
  pinMode        (C, OUTPUT);
  pinMode        (D, OUTPUT);
  pinMode   (enable, OUTPUT);
  switchScore = 0;
  x =  0;
  t = (0.0128*sq(x))-(0.64*x)+16;

}

void loop() {
  switch1State   =  digitalRead(switch1);
  switch2State   =  digitalRead(switch2);
  switch3State   =  digitalRead(switch3);
  switch4State   =  digitalRead(switch4);
  switch5State   =  digitalRead(switch5);
  motorCh1State  = digitalRead(motorCh1);
  motorCh2State  = digitalRead(motorCh2);
  
//BREIF:
       //All switches and motor channels are continuously tested. If the motorCh1 is high the
       //target turns to face before returning to test switches and motor channels again.
       //If a switch is pressed a number is added to switchScore so that switchScore can be
       //later tested to determine which switch(es) has/have been pressed. When motorCh2 is  
       //high target is turned to side and then programme reads switchScore value to determine
       //which switch(es) was/were pressed. The appropraite scrChannels are then activated to
       //signal which switch(es) was/were pressed. For subroutine scr3 there are multiple 
       //channels sent high, therefore there is a delay between each channel being sent high,
       //since only one channel can be sent high at a time. When each channel is set high it is
       //set high for a duration of 1s to ensure the Score Converter Chip can read the signal.
       //After each signal has been sent the switchScore value is reset.

       
if (switch1State  !=  lastSwitch1State){
  if(switch1State ==  HIGH){
    switchScore +=  16;
  }
  lastSwitch1State  =  switch1State;    
}

if (switch2State  !=  lastSwitch2State){
  if(switch2State ==  HIGH){
    switchScore +=  8;
  }
  lastSwitch2State  =  switch2State;    
}

if (switch3State  !=  lastSwitch3State){
  if(switch3State ==  HIGH){
    switchScore +=  4;
  }
  lastSwitch3State  =  switch3State;    
}

if (switch4State  !=  lastSwitch4State){
  if(switch4State ==  HIGH){
    switchScore +=  2;
  }
  lastSwitch4State  =  switch4State;    
}

if (switch5State  !=  lastSwitch5State){
  if(switch5State ==  HIGH){
    switchScore +=  1;
  }
  lastSwitch5State  =  switch5State;    
}

if  (motorCh1State ==  HIGH) {
  motorF();
}

if (motorCh2State  ==  HIGH)  {
  motorS();
  if  ((switchScore  = 16)||(switchScore  = 24))  {
  scr1();
}
  if  ((switchScore  = 8)||(switchScore  = 12))  {
  scr2();
}
  if  ((switchScore  = 4)||(switchScore  = 6))  {
  scr3();
}
  if  ((switchScore  = 2)||(switchScore  = 1))  {
  scr4();
}
  if  (switchScore  = 1)  {
  scr5();
}
}
}

//   _Ch1_|_Ch2_|_Ch3_
//  |_ 0 _|_ 0 _|_ 0 _| -----
//  |_ 0_ |_ 0 _|_ 1 _| = scr1
//  |_ 0_ |_ 1 _|_ 0 _| = scr2
//  |_ 0 _|_ 1 _|_ 1 _| = scr3
//  |_ 1 _|_ 0 _|_ 0 _| = scr4
//  |_ 1 _|_ 0 _|_ 1 _| = scr5
//  |_ 1 _|_ 1 _|_ 0 _| ------
//  |_ 1 _|_ 1 _|_ 1 _| ------


//subroutines for scoring:
void scr1() {
  digitalWrite(scrCh3,  HIGH);
  delay(1000);
  digitalWrite(scrCh3,  LOW);
  switchScore = 0;
  return;
}

void scr2() {
  digitalWrite(scrCh2,  HIGH);
  delay(1000);
  digitalWrite(scrCh2,  LOW);
  switchScore = 0;
  return;
}

void scr3() {
  digitalWrite(scrCh2,  HIGH);
  delay (200);
  digitalWrite(scrCh3,  HIGH);
  delay(1000);
  digitalWrite(scrCh2,  LOW);
  delay (200);
  digitalWrite(scrCh3,  LOW);
  switchScore = 0;
  return;
}

void scr4() {
  digitalWrite(scrCh1,  HIGH);
  delay(1000);
  digitalWrite(scrCh1,  LOW);
  switchScore = 0;
  return;
}

void scr5() {
  digitalWrite(scrCh1,  HIGH);
  delay(200);
  digitalWrite(scrCh3,  HIGH);
  delay(1000);
  digitalWrite(scrCh1,  LOW);
  delay(200);
  digitalWrite(scrCh3,  LOW);
  switchScore = 0;
  return;
}

// subroutine for turning target to face position
void  motorF() {
  
 digitalWrite (enable,HIGH);
 digitalWrite (A,HIGH);
 digitalWrite (B,HIGH);
 digitalWrite (D,LOW);
 x  +=  1;
 if (x > 50) {
    x = 0;
    digitalWrite (enable,LOW);
    return;
  }
 delay(t);
 digitalWrite (A,LOW);
 digitalWrite (C,HIGH);
 x  +=  1;
 if (x > 50) {
    x = 0;
    digitalWrite (enable,LOW);
    return;
  }
 delay(t);
 digitalWrite (B,LOW);
 digitalWrite (D,HIGH);
 x  +=  1;
 if (x > 50) {
    x = 0;
    digitalWrite (enable,LOW);
    return;
  }
 delay(t);
 digitalWrite (C,LOW);
 digitalWrite (A,HIGH);
 x  +=  1;
 if (x > 50) {
    x = 0;
    digitalWrite (enable,LOW);
    return;
  }
 delay(t);
 if (x  < 50){
  motorF();
 }
}

// subroutine for turning target to side position
void  motorS() {
  
 digitalWrite (enable,HIGH);
 digitalWrite (A,HIGH);
 digitalWrite (D,HIGH);
 digitalWrite (B,LOW);
 x  +=  1;
 if (x > 50) {
    x = 0;
    digitalWrite (enable,LOW);
    return;
  }
 delay(t);
 digitalWrite (A,LOW);
 digitalWrite (C,HIGH);
 x  +=  1;
 if (x > 50) {
    x = 0;
    digitalWrite (enable,LOW);
    return;
  }
 delay(t);
 digitalWrite (D,LOW);
 digitalWrite (B,HIGH);
 x  +=  1;
 if (x > 50) {
    x = 0;
    digitalWrite (enable,LOW);
    return;
  }
 delay(t);
 digitalWrite (C,LOW);
 digitalWrite (A,HIGH);
 x  +=  1;
 if (x > 50) {
    x = 0;
    digitalWrite (enable,LOW);
    return;
  }
 delay(t);
 if (x  < 50){
  motorS();
 }
}

