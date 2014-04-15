#include <Servo.h>

#define SERVO_PIN 3
#define SQUIRTER_PIN 9
#define RED_PIN 5
#define YELLOW_PIN 6
#define GREEN_PIN 7
#define MIN_ANGLE 60
#define MAX_ANGLE 140
#define NUMBER_OF_SWEEPS 2
#define TIME_BETWEEN_SWEEPS 20000

Servo servo;

int pos = 0;
boolean squirting = false;
boolean turning = false;
void setup() {
  Serial.begin(9600);
  servo.attach(SERVO_PIN);
  pinMode(SQUIRTER_PIN, OUTPUT);
}
void loop() {
  while(Serial.available() > 0 ) {
    char data = Serial.read(); 
    if (data == 'w') {
      water_sweep_once();
    }
  }
  if ( (millis() % 20000) == 0) {
    for(int i =0;i< TIME_BETWEEN_SWEEPS; i++) {
      water_sweep_once();
    }
  }
  delay(20000);
}

void water_sweep_once() {
    digitalWrite(SQUIRTER_PIN,HIGH);
    sweep_once();
    digitalWrite(SQUIRTER_PIN, LOW);
}

void sweep_once() {
  for(pos = MIN_ANGLE; pos < MAX_ANGLE; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    servo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = MAX_ANGLE; pos>=MIN_ANGLE; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    servo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
}

