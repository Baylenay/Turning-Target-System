const int motorCh1    = 2;
const int motorCh2    = 3;
const int A           = 7;
const int B           = 8;
const int C           = 9;
const int D           = 10;
const int enable      = 11;  
int motorCh1State     =  0;
int motorCh2State     =  0;
int x;
int t;

void setup() {
  pinMode  (motorCh1, INPUT);
  pinMode  (motorCh2, INPUT);
  pinMode        (A, OUTPUT);
  pinMode        (B, OUTPUT);
  pinMode        (C, OUTPUT);
  pinMode        (D, OUTPUT);
  pinMode   (enable, OUTPUT);
  x =  0;
  t = (0.0128*sq(x))-(0.64*x)+16;

}

void loop() {
  motorCh1State  = digitalRead(motorCh1);
  motorCh2State  = digitalRead(motorCh2);

  motorF();
  delay(1000);
  motorS();
  delay(1000);
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
