#include <Arduino.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#define RXD 8
#define TXD 7
SoftwareSerial hc06(RXD,TXD);
Servo myservo;
const int servoAnalogOut = A2;
const int x_pin = A0;
const int y_pin = A1;
unsigned int servoValue0Deg, servoValue180Deg;
int lever_value = 0;
int x_value = 0;
int y_value = 0;
void calibration(){
  myservo.write(0); //set the servo to 0 position
  delay(2000); //wait for the servo to reach there
  servoValue0Deg= analogRead(servoAnalogOut); // Pot value at 0 degrees
  Serial.println("Pot value for 0 deg is " + String(servoValue0Deg)); // Print it!
  delay(500); //fancy delay
  myservo.write(180); //go to 180 degrees
  delay(2000); //wait for the servo to reach there
  servoValue180Deg= analogRead(servoAnalogOut); //pot value at 180 deg
  Serial.println("Pot value for 180 deg is " + String(servoValue180Deg));
  delay(500); //fancy delay 
  Serial.println("Now going to 0 Degrees"); //It does what it says
  myservo.write(0);// going to 90 degrees
  delay(2000);// wait for it to reach there
  myservo.detach(); // stop the PWM so that we can freely move the servo
  delay(1000);
}
void setup(){
  Serial.begin(9600);
  hc06.begin(9600);
  myservo.attach(2);  
  // calibration();
}
void loop(){
  if(hc06.available()){
    Serial.write(hc06.read());
  }
  if(Serial.available()){
    hc06.write(Serial.read());
  }
  /*
  lever_value = map(analogRead(servoAnalogOut),servoValue0Deg,servoValue180Deg, 0, 180);
  if(lever_value < 0){
    lever_value = 0;
  }
  x_value = analogRead(x_pin);
  y_value = analogRead(y_pin);
  Serial.print(lever_value);
  Serial.print("\t");
  Serial.print(x_value);
  Serial.print("\t");
  Serial.println(y_value);
  */

}
