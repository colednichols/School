/*

AUTHORS: Cole Nichols, Emery Denham, ______ ______
DATE: 1/24/2023
VERSION: 1.0

AUTHOR'S NOTES:
  - With more time, I would implement PID to improve efficiency, however, I have not worked with it before and would need to learn.
  - The optimization indicator LED tells the user when the tracking plane is going to look for a better position. 
  - I can also implement a transistor to turn off the servo when not in movement and save power.   

*/

#include <Servo.h>

Servo myservo;  // create object to control servo

// CALIBRATION VALUES
const int STEP_DEGREES = 10;       // variable to set number of degrees servo turns upon each reading
const int STEPS_PER_LOOP = 3;      // variable to set number of steps servo turns upon each search loop
const int MOVE_DELAY_FAST = 15;    // variable to set time between servo movement and photocell reading
const int MOVE_DELAY_SLOW = 500;   // variable to set time between servo movement and photocell reading
const int LOOP_DELAY = 500;       // variable to set time between optimize loops
const int SERVO_LIMIT_MIN = 10;     // variable to set minimum servo position [30]
const int SERVO_LIMIT_MAX = 170;   // variable to set maximum servo position [130]
const int SERVO_CENTER = 90;       // variable to set base servo position [80]
const float LOOP_TOLORANCE = 10;   // variable to set tolarance for photoresistor changes (Ex. 12.5 = 12.5%)

// OTHER CONSTANTS
const int SERVO_LOOP_POS_MIN = SERVO_LIMIT_MIN + STEP_DEGREES;  // variable to set minimum servo position for loop
const int SERVO_LOOP_POS_MAX = SERVO_LIMIT_MAX - STEP_DEGREES;  // variable to set maximum servo position for loop

// VARIABLES 
int trackPin = A0;            // pin for tracking photoresistor
int trackValue = 0;           // variable to store value read from tracking photoresistor
int baseTrackValue = 0;       // variable to store value read from tracking photoresistor upon last loop
int servoPos = 90;            // variable to store current servo position
int baseServoPos = 90;        // variable to store servo position before movement
int maxTrackValue = 0;        // variable to store max value read from tracking photoresistor
int maxTrackPos = 0;          // variable to store servo position where max value was read
int toleratedTrackValue = 0;  // variable to store an adjusted value derived from the tracking photoresistor ( maxTrackValue * ( 1 + ( LOOP_TOLORANCE * 0.01 ) ) )
bool broadSearch = true;

void setup() {

  pinMode(LED_BUILTIN, OUTPUT); // enables optimize indicator LED
  myservo.attach(11);           // attaches servo on pin 9 to servo object

}

void loop() {
  // STARTUP PROCEDURE
  if(broadSearch == true) {
    
    myservo.write(SERVO_CENTER);  // moves servo to desired neutral position
    delay(3000);                  // allows user to properly allign tracking plane

    myservo.write(SERVO_LIMIT_MIN); // moves servo to minimum position in preperation for startup procedure
    delay(1000);                    // allows servo to move into place
    
    for (servoPos = SERVO_LIMIT_MIN; servoPos < SERVO_LIMIT_MAX; servoPos += 1) {  // move servo to right by 1 degree until limit

      myservo.write(servoPos);            // move servo to incremented position
      delay(MOVE_DELAY_FAST);             // allows servo to move into place
      trackValue = analogRead(trackPin);  // read value from tracking photoresistor

      if (trackValue > maxTrackValue) { // if current estimated efficiency value exceeds previous record

        maxTrackValue = trackValue; // set efficiency record
        maxTrackPos = servoPos;     // set prefered position to current position

      }

    }  

    myservo.write(maxTrackPos); // move servo to estimated optimal position
    servoPos = maxTrackPos;     // set current servo position variable to true position

    broadSearch = false;  // sets variable to false so the "startup procedure" section does not run again

  }

  // TRACKING LOOP
  toleratedTrackValue = maxTrackValue * ( 1 - ( LOOP_TOLORANCE * 0.01 ) );  // set toleranced track value variable to adjusted value

  trackValue = analogRead(trackPin);  // read value from tracking photoresistor

  if (trackValue < toleratedTrackValue) {  // if resistance across tracking photoresistor rises above tolerated level

    digitalWrite(LED_BUILTIN, HIGH);  // turn optimization indicator LED on
    delay(100);                       // delay to determine indicator LED on time
    digitalWrite(LED_BUILTIN, LOW);   // turn optimization indicator LED off

    maxTrackValue = trackValue; // set efficiency record
    baseServoPos = servoPos;    // set base servo position variable to current position for later reference
    
    for (int i = 0; i < STEPS_PER_LOOP && servoPos <= SERVO_LOOP_POS_MAX; i++) {  // loop to move servo forward and check if position is better

      servoPos += STEP_DEGREES; // increment servo position variable by step variable
      myservo.write(servoPos);  // move servo to incremented position
      
      delay(MOVE_DELAY_SLOW); // delay allows servo to move before measurement

      trackValue = analogRead(trackPin);  // read value from tracking photoresistor

      if (trackValue > maxTrackValue) { // if current estimated efficiency value exceeds previous record

        digitalWrite(LED_BUILTIN, HIGH);  // turn optimization indicator LED on
        delay(50);                        // delay to determine indicator LED on time
        digitalWrite(LED_BUILTIN, LOW);   // turn optimization indicator LED off

        maxTrackValue = trackValue; // set efficiency record
        maxTrackPos = servoPos;     // set prefered position to current position

      }

    }

    servoPos = baseServoPos;                    // sets servo position to the starting position
    myservo.write(servoPos);                    // move servo to base position
    delay((MOVE_DELAY_FAST * STEPS_PER_LOOP));  // delay allows servo to move to base position

    for (int i = 0; i <= STEPS_PER_LOOP && servoPos >= SERVO_LOOP_POS_MIN; i++) {  // loop to move servo backward and check if position is better

      servoPos -= STEP_DEGREES; // decrement servo position variable by step variable
      myservo.write(servoPos);  // move servo to decremented position
      
      delay(MOVE_DELAY_SLOW);  // delay allows servo to move before measurement

      trackValue = analogRead(trackPin); // read value from tracking photoresistor
      
      if (trackValue > maxTrackValue) { // if current estimated efficiency value exceeds previous record

        digitalWrite(LED_BUILTIN, HIGH);  // turn optimization indicator LED on
        delay(50);                        // delay to determine indicator LED on time
        digitalWrite(LED_BUILTIN, LOW);   // turn optimization indicator LED off

        maxTrackValue = trackValue; // set efficiency record
        maxTrackPos = servoPos;     // set prefered position to current position

      }
      
    }
    
    servoPos = maxTrackPos;
    myservo.write(servoPos);                // move servo to estimated optimal position
    baseTrackValue = analogRead(trackPin);  // set base tracking photoresistor variable to value read from tracking photoresistor

    delay(LOOP_DELAY);  // delay prevents code from looping too quickly

  }

}
