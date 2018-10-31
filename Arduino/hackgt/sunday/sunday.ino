#include <Adafruit_NeoPixel.h>
#include <Bridge.h>
#include <Process.h>
#include <Servo.h>
#include <Stepper.h>
#define PIN 6

Process p;
Servo myServo;
const int stepsPerRevolution = 4;
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);
void setup() {
  digitalWrite(13, LOW);
  delay(1000);
  strip.begin();
//  strip.show(); // Initialize all pixels to 'off'
  //set pixel color number, red, green, blue
//  for(int i=0; i<16; i++)
//    strip.setPixelColor(i, 0 , 0, 0);
  strip.show();
  myStepper.setSpeed(20);
  myServo.attach(12);

  Serial.begin(9600);
}

void loop() {
  digitalWrite(13, HIGH);
  int angle;
  delay(1000);
  while(Serial.available()>0) {
    digitalWrite(13, LOW);
    angle = Serial.read();
    if(angle == 'a'){ // food do nothing
       dumpTrash();
    } else if(angle == 'b') { // drink rotate 120 deg
      myStepper.step(1);
      dumpTrash();
      myStepper.step(-1);
    } else { // lanfill rotate 240 deg
      myStepper.step(-1);
      dumpTrash();
      myStepper.step(1);
    }
    delay(2000);
  }
}

void dumpTrash(){
  for (int pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myServo.write(pos);   
    delay(20);   
  }
  delay(500);
  for (int pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myServo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  } 
 }
