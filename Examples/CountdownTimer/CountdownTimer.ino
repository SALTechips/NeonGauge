/*Program which uses all 3 neon tubes as a countdown timer.
  The neon tubes are fully on at 60 hours, 60 minutes and 60 seconds. Note that
  60 hours/minutes/seconds are represented by a 240 PWM signal and the PWM singal is decreasing by steps of 4 each time.
  Connect the Rx pin of your NeonGauge product to pin 1 of the Arduino.
*/

#include <NeonGauge.h>

#define user_hours 0 // SET HOURS HERE
#define user_mins 30 // SET MINUTES HERE
#define user_secs 20 // SET SECONDS HERE

int minbar; // Holds the PWM number of the minutes
int secbar; // Holds the PWM number of the seconds
int hourbar; // Holds the PWM number of the hours
long previoussec=0; // Helps for defining one second
long interval_sec=1000; // Helps for defining one second
int Start=1; // Helps in defining the initial states of the Countdown Timer
int stop_c=0; // Becomes 1 whenever the countdown finishes

/* If you are using the SoftwareSerial library initialize the NeonGuage object as: 
    -- NeonGauge timer(&mySerial) , where mySerial is name of the SoftwareSerial object 
   If a hardware serial pin is used then no HardwareSerial object declaration is required and you simply need to initialize the NeonGauge object as:
    -- NeonGauge vumeter(&Serial) or
    -- NeonGauge vumeter(&Serial1) etc, depending on the hardware serial ports that your arduino provides.
*/ 
NeonGauge timer(&Serial); // HarwareSerial is being used here (pin 1 of the Arduino UNO)

void setup() {
  timer.begin(9600);
}

void loop() {  
  unsigned long cur_timer=millis(); // Holds the time in milliseconds from the moment the program runs
  if (stop_c==0){
    //Initial conditions
    if (Start==1){
      if (user_secs==0){
        secbar=236;
        if (user_mins==0) {
          minbar=236;
          if (user_hours==0){ // This is the case in which the user gave 0hours,0minutes,0seconds
            timer.BlinkNeon(1); // Blink them ON,OFF,ON and OFF at a period of 1sec
            stop_c=1;  
          }
          else hourbar=(240/60)*(user_hours-1); // For e.g if the user gives countdown(2,0,0) then this will become (1,59,59)
        }
        else minbar=(240/60)*(user_mins-1); // For e.g if the user gives countdown(0,2,0) then this will become (0,1,59)
      }    
      else { // Map the hours, minutes and seconds to their corresponding PWM values
        secbar=(240/60)*user_secs;
        hourbar=(240/60)*user_hours;
        minbar=(240/60)*user_mins;
      }
      // Write the corresponding PWM values to the neon tubes
      timer.setPWM(1,hourbar);
      timer.setPWM(2,minbar);
      timer.setPWM(3,secbar);
      Start=0; // Initial conditions finished
    }
    // Every 1 sec we refresh the PWM of the neon tubes in order to decrease the height of illumination 
    if ( (cur_timer-previoussec>interval_sec)){  
      previoussec=cur_timer;
      secbar-=4;
      timer.setPWM(3,secbar);
      if (secbar==-4) { // Here the neon tube which represents the seconds is at its minimum illumination height and we set secbar to 236 in order to be ready to start counting down from 59s, if the countdown has not yet finished
        secbar=236;
        if (minbar!=0){
          minbar-=4;
          timer.setPWM(2,minbar);
        }
        else {
          if (hourbar!=0){
              minbar=236;
              hourbar-=4;
              timer.setPWM(1,hourbar);
              timer.setPWM(2,minbar);
          }
          else{ // The countdown has finished
            timer.BlinkNeon(1); // Blink them ON,OFF,ON and OFF at a period of 1sec
            stop_c=1; // Make it 1 as the countdown has finished
          }
        }
      }
    }
  }
}
