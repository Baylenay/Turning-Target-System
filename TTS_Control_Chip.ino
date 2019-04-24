#include <SevSeg.h>
SevSeg sevseg;
const int Mode1       =  A0;
const int Mode2       =  A1;
const int Buzzer      =  A2;
const int motorCh1    =  A3;
const int motorCh2    =  A4;
const int sensorPin   =  A5;
int setSwitchState    =   0;
int Mode1State        =   0;
int Mode2State        =   0;
int MotorState        =   0;
int sensorValue       =   0;


void setup() {
  pinMode       (Mode1, INPUT);
  pinMode       (Mode2, INPUT);
  pinMode       (Buzzer,OUTPUT);
  pinMode       (motorCh1, OUTPUT);
  pinMode       (motorCh2, OUTPUT);
  byte          numDigits = 4;
  byte          digitPins[] = {2, 3, 4, 5};
  byte          segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);
  sevseg.setBrightness(2.75);
}

// the loop routine runs over and over again forever:
void loop() {
  Mode1State     =   digitalRead      (Mode1);
  Mode2State     =   digitalRead      (Mode2);
  sensorValue    =   analogRead   (sensorPin);

//BREIF: TRAINING MODE - (MODE1)
      //A buzzer will initially sound for a period of 2 seconds to indicate to the shooter
      //to load. A potentiometer dial can be turned to vary the time delay, from a min. of
      //5s to a max. of 30s, between the load signal and the first command. The first command  
      //"Are you ready?"  will be represented by a 1 seconds buzz. The second and third commands
      //will follow 1 second after each other with the same duration of buzz as command 1.
      //First command - "Watch".  Second command  - "Shoot". For every commanding the
      //corresponding number of that command will be displayed in sync. A 3 second count-down
      //will follow with numbers 3, 2 and 1 being displayed. After 3 seconds the buzzer will
      //sound for 0.5s as the target turns to face. numbers 1-4 will be displayed between the
      //4 second period. After 4 seconds buzzer sounds for 0.5s as target turns to side.
      //This routine is then repeated 10 times before stopping.

if (Mode1State == HIGH) {
  for (int shots  = 0;shots<10;shots++)  //repeat training mode routine 10 times before stoppoing
{ tone  (A2, 1000);
  delay         (2000);                  //sound buzzer for 2 seconds to indicate to the shooter
  noTone      (Buzzer);                  //that they must load
                                         // variable time delay for loading
  delay (5000+(sensorValue*25));         //can be changed from 5s min. to 30s max.
                                         //first command:
  tone  (A2, 1000);                      //sound buzzer and display number 1 for 1 second
  for(int d =  0;d < 1000;d++) {         //to indicate first command - "Are you ready?"
    sevseg.setNumber(0001,0);
    sevseg.refreshDisplay();
  }
  noTone  (A2);
  delay                 (1000);          //wait 1 second before executing second command
                                         //second command:
  tone  (A2, 1000);                      //sound buzzer and display number 2 for 1 second
  for(int d =  0;d < 1000;d++) {         //to indicate second command - "Watch"
    sevseg.setNumber(0002,0);
    sevseg.refreshDisplay();
  }
  noTone  (A2);
  delay                 (1000);          //wait a second before executing third command
                                         //third command:
  tone  (A2, 1000);                      //sound buzzer and display number 3 for 0.5 seconds
  for(int d =  0;d < 500;d++) {          //to indicate third command - "Shoot"
    sevseg.setNumber(0003,0);
    sevseg.refreshDisplay();
  }
  noTone  (A2);
  delay                  (500);         //wait 0.5 seconds before count-down
                                        // count-down:
  for(int d =  0;d < 500;d++) {      
    sevseg.setNumber(0002,0);              
    sevseg.refreshDisplay();
  }               
  delay                  (500);         //counts down before target turns from 3 to 1       
  for(int d =  0;d < 1000;d++) {           
    sevseg.setNumber(0001,0);              
    sevseg.refreshDisplay();               
  }
                                        //Target turns:
  tone (A2,  1000);                     //buzzer sounds to indicate motor is turning
  motorF();                             //turns motor to face
  noTone  (A2);          //buzzer finishes sounding with time period of 0.5s
  delay                  (500);
  for(int d =  0;d < 500;d++) {         //1 second after target turns, 1 is displayed for 0.5s
    sevseg.setNumber(0001,0);
    sevseg.refreshDisplay();
  }
  delay                  (500);
  for(int d =  0;d < 500;d++) {         //2 is displayed for 0.5s 
    sevseg.setNumber(0002,0);
    sevseg.refreshDisplay();
  }
  delay                  (500);
  for(int d =  0;d < 312;d++) {         //3 is displayed for 0.5s 
    sevseg.setNumber(0003,0);
    sevseg.refreshDisplay();
  }
  delay                  (500);
  tone (A2,  1000);            //after 4s buzzer sounds and target turns to side
  motorS();
  noTone  (A2);          //buzzer finishes sounding with time period of 0.5s 
  for(int d =  0;d < 500;d++) {         //4 is displayed 0.5s after target turns for 0.5s
    sevseg.setNumber(0004,0);
    sevseg.refreshDisplay();
  }
  }
  }
  // END OF TRAINING MODE ROUTINE //


//BREIF: COMPETITION MODE - (MODE2)
      //A count down will begin from 1-3 displaying number 1-3 at the corresponding time.
      //After 3 seconds the target will turn to face. Numbers 1-4 will be displayed at the
      //corresponding time after the tagret has turned to face. After 4 seconds the target will
      //turn to side and the routine will end.

      
if  (Mode2State ==  HIGH)  {
                                       //count-down
  delay                 (500);
  for(int d =  0;d < 500;d++) {        //1 is displayed for 0.5s
    sevseg.setNumber(0001,0);
    sevseg.refreshDisplay();
  }
  delay                  (500);
  for(int d =  0;d < 500;d++) {        //2 is displayed for 0.5s
    sevseg.setNumber(0002,0);
    sevseg.refreshDisplay();
  }
  delay                  (500);
  for(int d =  0;d < 500;d++) {        //3 is displayed for 0.5s
    sevseg.setNumber(0003,0);
    sevseg.refreshDisplay();
  }
  // Target turns:
  motorF();                            //target turns to face, total time = 0.5s
  delay                  (500);        
  for(int d =  0;d < 500;d++) {        //1 second after target turns, 1 is displayed for 0.5s
    sevseg.setNumber(0001,0);
    sevseg.refreshDisplay();
  }
  delay                  (500);
  for(int d =  0;d < 500;d++) {        //2 is displayed for 0.5s
    sevseg.setNumber(0002,0);
    sevseg.refreshDisplay();
  }
  delay                  (500);
  for(int d =  0;d < 500;d++) {        //3 is displayed for 0.5s
    sevseg.setNumber(0003,0);
    sevseg.refreshDisplay();
  }
  delay                  (500);
  motorS();                            //target turns to side, total time = 0.5s
  for(int d =  0;d < 500;d++) {       //4 is displayed 0.5s after target turns for 0.5s       
    sevseg.setNumber(0004,0);
    sevseg.refreshDisplay();
  }
  }
  }
  // END OF COMPETITION MODE ROUTINE //


// subroutine for turning target to face position
void motorF() {
  digitalWrite (motorCh1, HIGH);
  delay(500);
  digitalWrite  (motorCh1, LOW);
  return;
}

// subroutine for turning target to side position
void motorS() {
  digitalWrite (motorCh2, HIGH);
  delay                   (500);
  digitalWrite  (motorCh2, LOW);
  return;
}

