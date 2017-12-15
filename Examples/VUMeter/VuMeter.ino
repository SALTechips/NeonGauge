/*VU meter application (Note that the Rx pin of the Neongauge product should be connected at 
  pin 11 (Tx pin) of the Arduino, for this example. By using the SoftwareSerial library, you can also use any of the allowed Rx and Tx pins on the Arduino). Required to have:
  --Winamp.
  --lcd_analyzer.ini (inside C:\) (https://github.com/SALTechips/NeonGauge/tree/master/extras)
  --gen_crownsoft_lcd.dll (inside C:\... Winamp\Plugins) (https://github.com/SALTechips/NeonGauge/tree/master/extras)
  --SoftwareSerial library.
  Please note that you must first upload the sketch on the Arduino (with Winamp closed) and then open Winamp.
*/
#include <NeonGauge.h>
#include <SoftwareSerial.h> //Verion 1.0.0 used. Available from the Library Manager as "SoftwareSerial".

SoftwareSerial mySerial(10, 11); //Rx=10, Tx=11. You can also use any of the allowed Rx and Tx pins on the Arduino
/* If you are using the SoftwareSerial library initialize the NeonGuage object as shown below (do not forget the "&"). If a hardware serial pin is used then
   no HardwareSerial object declaration is required and you simply need to initialize the NeonGauge object as shown below:
    -- NeonGauge vumeter(&Serial) or
    -- NeonGauge vumeter(&Serial1) etc, depending on the hardware serial ports that your arduino provides.
*/ 
NeonGauge vumeter(&mySerial);

/*As long as the Plugin has been installed, WINAMP will send commands to the serial port of the computer. 
  Initially the ASCII code j or k are being sent which indicate the following:
    j-> Command that indicates that an amplitude will be written.
    k-> Clear the neon tubes
    i-> As the initial purpose of the this winamp pluging was to create a vu meter on an lcd, this ASCII code was used to clear a give position (column,row) of the lcd
  If j is given then a numnber from 0 to 15 is sent according to the frequency bin of the sound and then another number from 0 to 1 which is the
  first indicator of the sound level. The last commnad is an ASCII code (a, b, c, d, e, f, g, h) and has one of the following meanings:
  a-> Amplitude = 1
  b-> Amplitude = 2
  c-> Amplitude = 3
  d-> Amplitude = 4
  e-> Amplitude = 5
  f-> Amplitude = 6
  g-> Amplitude = 7
  h-> Amplitude = 8
*/


byte level_1=0;
byte level_2=0;
byte level_3=0;
int sum_1=0;
int sum_2=0;
int sum_3=0;
byte vol1,vol2,vol3;
int display1=0;
int display2=0;
int display3=0;
long previousMillis=0;
unsigned long currentMillis=0;

// Function for reading incoming data
byte serial_getch(void) {
  while (Serial.available() == 0){
    currentMillis=millis();   
    if (currentMillis-previousMillis>50){
      vumeter.reset(); // Reset the neon tubes 50ms after the user has stopped playing the music track
    }
  }
  previousMillis=currentMillis;
  return Serial.read();
}
  
void setup() {
  Serial.begin(9600);
  vumeter.begin(9600);
}

void loop() {
  byte rxbyte = serial_getch(); // The initial incoming code can be either j k
  if (rxbyte == 'j'){
    byte freq = serial_getch()-'0'; // A number from 0 to 15 depending on the frequency of the sound
    byte level_0 = serial_getch()-'0'; // First indicator of the amplitude
    byte level = serial_getch()-'a'; // Indicates sound amplitude which can be: 0, 1, 2,... ,7

    // We take the average of the first 4 sound frequencies to display it on the first neon tube
    if (freq>=0 && freq<=3){
      if (level_0==0){
        level_1+=level;
        sum_1+=1;  
      }
      else if (level_0==1){
        level_1+=level+7;
        sum_1+=1;
      }
      if (sum_1==4){
        display1=1;  
        level_1=level_1>>2; 
      }
    }
    
    // We take the average of the next 4 sound frequencies to display it on the second neon tube
    else if (freq>=4 && freq<=7){
      if (level_0==0){
        level_2+=level;
        sum_2+=1;  
      }
      else if (level_0==1){
        level_2+=level+7;
        sum_2+=1;
      }
      if (sum_2==4){
        display2=1; 
        level_2=level_2>>2; 
      }       
    }

    // We take the average of the last 4 sound frequencies to display it on the third neon tube
    else if (freq>=12 && freq<=15){
      if (level_0==0){
        level_3+=level;
        sum_3+=1;  
      }  
      else if (level_0==1){
        level_3+=level+7;
        sum_3+=1;
      }
      if (sum_3==4){
        display3=1;  
        level_3=level_3>>2; 
      }      
    }     
    // We display the averages on the three neon tubes and reset the variables used
    if (display1==1){   
      vol1=map(level_1,0,14,0,240); // The maximum PWM signal is 240 becasue a higher value overdrives the neon tubes
      vol1=level_1*18;
      vumeter.setPWM(1 ,vol1);
      display1=0;
      sum_1=0;
      level_1=0;
      vol1=0;
    }
    if (display2==1){
      vol2=map(level_2,0,14,0,240); // The maximum PWM signal is 240 becasue a higher value overdrives the neon tubes
      vumeter.setPWM(2 ,vol2);
      display2=0;
      sum_2=0;
      level_2=0;
      vol2=0;
    }    
    if (display3==1){
      vol3=map(level_3,0,14,0,240); // The maximum PWM signal is 240 becasue a higher value overdrives the neon tubes
      vumeter.setPWM(3 ,vol3);
      display3=0;
      sum_3=0;
      level_3=0;
      vol3=0;      
    }    
  }
  else if (rxbyte == 'k'){
    vumeter.reset(); // Reset the neon tubes 
  }
  // As the initial purpose of the this winamp pluging was to create a vu meter on an lcd, the "i" ASCII code was used to clear a give position (column,row) of the lcd. 
  // Thus, here we read this position to make sure that the reveiving buffer of the Arduino does not get full and we reset the neon tubes.
  else if (rxbyte == 'i'){ 
    byte column = serial_getch()-'0'; 
    byte row = serial_getch()-'0';
 
  }
}

