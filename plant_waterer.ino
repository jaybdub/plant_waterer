#include <Servo.h>

#define SERVO_PIN 3
#define SQUIRTER_PIN 9
#define RED_PIN 5
#define YELLOW_PIN 6
#define GREEN_PIN 7
#define MIN_ANGLE 60
#define MAX_ANGLE 143
#define NUMBER_OF_SWEEPS 2
#define WATERING_INTERVAL_MS 60000*15

int pos;
long time_of_last_watering;
Servo servo;

void setup() {
  servo.attach(SERVO_PIN);
  pinMode(SQUIRTER_PIN, OUTPUT);
}
void loop() {
  if((millis() - time_of_last_watering) > WATERING_INTERVAL_MS) {
    for (int i=0; i < NUMBER_OF_SWEEPS; i++){
      water_sweep_once();
    }
    time_of_last_watering = millis();
  }
  delay(100);
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

