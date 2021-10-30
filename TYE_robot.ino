
#include <IRremote.h>
#include <Servo.h>

IRrecv irrecv(7);
decode_results results;
unsigned long key_value = 0;

Servo left;
Servo right;

int state = 0;
double speedL = 0; //speed given from -10 to 10
double speedR = 0; //speed given from -10 to 10 *NOTE: because the right motor is flipped, writeMicroseconds values will be reversed


void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn();
  
  left.attach(A0);
  right.attach(A1);

  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);

  
}

void loop(){

  state = 0;
  
  if (irrecv.decode(&results)){
 
        if (results.value == 0xFFFFFFFF)
          results.value = key_value;

        switch(results.value){
          case 0xFFA25D:
            Serial.println("1");
            break;
          case 0xFF629D:
            Serial.println("2");
            break;
          case 0xFFE21D:
            Serial.println("3");
            break;
          case 0xFF22DD:
            Serial.println("4");
            break;
          case 0xFF02FD:
            Serial.println("5");
            break;  
          case 0xFFC23D:
            Serial.println("6");
            break;               
          case 0xFFE01F:
            Serial.println("7");
            break;  
          case 0xFFA857:
            Serial.println("8");
            break;  
          case 0xFF906F:
            Serial.println("9");
            break;  
          case 0xFF6897:
            Serial.println("*");
            break;  
          case 0xFF9867:
            Serial.println("0");
            break;
          case 0xFFB04F:
            Serial.println("#");
            break;
          case 0xFF30CF:
            Serial.println("");
            break;
          case 0xFF18E7:
            Serial.println("^");
            state = 1;
            break;
          case 0xFF7A85:
            Serial.println("");
            break;
          case 0xFF10EF:
            Serial.println("<");
            state = 3;
            break;
          case 0xFF38C7:
            Serial.println("OK");
            state = 0;
            break;
          case 0xFF5AA5:
            Serial.println(">");
            state = 4;
            break;
          case 0xFF42BD:
            Serial.println("");
            break;
          case 0xFF4AB5:
            Serial.println("v");
            state = 2;
            break;
          case 0xFF52AD:
            Serial.println("");
            break;      
        }
        key_value = results.value;
        irrecv.resume(); 
  }
  
  
  switch(state) {
    case 0:
      Serial.println("state 0");
      speedL = 0;
      speedR = 0;
      break;
    case 1:
      Serial.println("state 1");
      speedL = 10;
      speedR = 10;
      break;
    case 2:
      Serial.println("state 2");
      speedL = -10;
      speedR = -10;
      break;
    case 3:
      Serial.println("state 3");
      speedL = 0;
      speedR = 10;
      break;
    case 4:
      Serial.println("state 4");
      speedL = 10;
      speedR = 0;
      break;
  }
  
  int microsecondsL = map(speedL, -10, 10, 1000, 2000);
  int microsecondsR = map(speedR, -10, 10, 2000, 1000);

  left.writeMicroseconds(microsecondsL);
  right.writeMicroseconds(microsecondsR);
  
  delay(50);
  
}
