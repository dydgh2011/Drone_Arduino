#include<Arduino.h>
#include "MPU9250.h"
#include <Servo.h>
// an MPU9250 object with the MPU-9250 sensor on I2C bus 0 with address 0x68
MPU9250 IMU(Wire,0x68);
Servo Left;
Servo Right;

int left_motor_pin = 10;
int right_motor_pin = 9;

int status;
int left_motor_value;
int right_motor_value;
// testing

Servo myservo;  // create servo object to control a servo
const int servoAnalogOut = A3; //The new Servo Pin
unsigned int servoValue0Deg, servoValue180Deg; // Vaiables to store min and max values of servo's pot
int pos = 0;    // variable to store the servo position
int motor_speed;



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
  Serial.println("Now going to 000 Degrees"); //It does what it says
  myservo.write(0);// going to 90 degrees
  delay(2000);// wait for it to reach there
  myservo.detach(); // stop the PWM so that we can freely move the servo
  delay(1000);
}

void setup() {
  // serial to display data
  Serial.begin(9600);
  while(!Serial) {}

  // start communication with IMU 
  status = IMU.begin();
  if (status < 0) {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while(1) {}
  }
  // setting the accelerometer full scale range to +/-8G 
  IMU.setAccelRange(MPU9250::ACCEL_RANGE_8G);
  // setting the gyroscope full scale range to +/-500 deg/s
  IMU.setGyroRange(MPU9250::GYRO_RANGE_500DPS);
  // setting DLPF bandwidth to 20 Hz
  IMU.setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_20HZ);
  // setting SRD to 19 for a 50 Hz update rate
  IMU.setSrd(19);
  
  // motor setting
  Left.attach(left_motor_pin,1000,2000);
  Right.attach(right_motor_pin,1000,2000);
  

  //testing
  myservo.attach(7);  
  // attaches the servo on pin 9 to the servo object
  calibration();
}

void loop() {
  // read the sensor
  /*
  IMU.readSensor();

  // display the data
  Serial.print(IMU.getAccelX_mss(),6);
  Serial.print("\t");
  Serial.print(IMU.getAccelY_mss(),6);
  Serial.print("\t");
  Serial.print(IMU.getAccelZ_mss(),6);
  Serial.print("\t");
  Serial.print(IMU.getGyroX_rads(),6);
  Serial.print("\t");
  Serial.print(IMU.getGyroY_rads(),6);
  Serial.print("\t");
  Serial.print(IMU.getGyroZ_rads(),6);
  Serial.print("\t");
  Serial.print(IMU.getMagX_uT(),6);
  Serial.print("\t");
  Serial.print(IMU.getMagY_uT(),6);
  Serial.print("\t");
  Serial.print(IMU.getMagZ_uT(),6);
  Serial.print("\t");
  Serial.println(IMU.getTemperature_C(),6);
  delay(20);
  */
  motor_speed = map(analogRead(servoAnalogOut),servoValue0Deg,servoValue180Deg, 0, 255);
  if(motor_speed < 0){
    motor_speed = 0;
  }
  Serial.println(motor_speed);
  Left.write(motor_speed);
  Right.write(motor_speed);
  delay(100);
}

