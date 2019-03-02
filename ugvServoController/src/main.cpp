#include <Arduino.h>
#include <Servo.h>

Servo myServo;

int pos = 0;


volatile int pwm_valueS = 0; //servo
volatile int prev_timeS = 0;

volatile int pwm_valueP = 0;  //pixracer
volatile int prev_timeP = 0;

void risingS();
void fallingS();
void risingP();
void fallingP();

void setup() {
    myServo.attach(5);

    // pinMode(A7, INPUT);


    Serial.begin(115200);
    // when pin D2 goes high, call the rising function
    attachInterrupt(0, risingS, RISING);
    // when pin D3 goes high, call the rising function
    attachInterrupt(1, risingP, RISING);
}

void loop() {
    for(int i = 0; i<pwm_valueP/250; i++){
        while(pwm_valueS < 100 || pwm_valueS > 600){
            myServo.write(180);
            delay(10);
        }
        // myServo.write(90);
        // delay(500);
        while(pwm_valueS < 600){
            myServo.write(180);
            delay(10);
        }
    }
    myServo.write(90);
    delay(500);
    Serial.print("Servo: ");
    Serial.println(pwm_valueS);
    Serial.print("PixRacer: ");
    Serial.println(pwm_valueP);
}

void risingS() {
  attachInterrupt(0, fallingS, FALLING);
  prev_timeS = micros();
}

void fallingS() {
  attachInterrupt(0, risingS, RISING);
  pwm_valueS = micros()-prev_timeS;
  // Serial.print("Servo: ");
  // Serial.println(pwm_valueS);
}

void risingP() {
  attachInterrupt(1, fallingP, FALLING);
  prev_timeP = micros();
}

void fallingP() {
  attachInterrupt(1, risingP, RISING);
  pwm_valueP = micros()-prev_timeP;
  // Serial.print("PixRacer: ");
  // Serial.println(pwm_valueP);
}
