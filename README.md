# NeonGauge Library
![alt text](https://github.com/SALTechips/NeonGauge/blob/master/extras/Neon%20Tubes.PNG)

Arduino Library for controlling the ***NeonGauge*** product.
## Functions
* **begin(BaudRate)**: Initializes the serial communication between the NeonGauge product and the Arduino. Please use 9600 as the Baud Rate.
* **reset()**: Resets the illumination of the neon tubes to zero.
* **sputtering()**: A process which cleans the cathode of the neon tubes from internal impurities to maintain display.
* **setPWM(channel,value)**: Sets the height of illumination of each neon tube to a desired value. Note that, there are three tubes and thus three channels.
* **BlinkNeon(period)**: Blinks the neon tubes ON, OFF, ON, OFF, at a desired period (in seconds).
## Installation
There are 3 was to install the NeonGauge Library.
### 1. From the Library Manager
Open the IDE and click to the "Sketch" menu and then Include Library > Manage Libraries and then search for "NeonGauge".
### 2. From Github
Download the following files from [***Github***](https://github.com/SALTechips/NeonGauge/).
*   **Examples**
*   **src**
*   **keywords.txt**

Place them inside a folder named "NeonGauge" and then place this folder inside ..\<you>\DOCUMENTS\Arduino\libraries. If you have arduino IDE opened make sure you restart it before you start using the library.
### 3. From SALTechips
Download the **(GIVE THE NAME OF THE ZIP FILE) from (GIVE URL)**

Unzip the content and place the "NeonGauge" folder inside ..\<you>\DOCUMENTS\Arduino\libraries. If you have Arduino IDE opened, make sure you restart it before you start using the library.

Further information on how to install an arduino library can be found [***here***](https://www.arduino.cc/en/Guide/Libraries).
## Examples
**Please use either of these examples to learn how to correctly define a NeonGauge object.**
### Countdown Timer.
This is a program which uses all 3 neon tubes as a countdown timer. The neon tubes are fully on at 60 hours, 60 minutes and 60 seconds. Note that 60 hours/minutes/seconds are represented by a 240 PWM signal and the PWM signal is decreasing by steps of 4 each time. Connect the Rx pin of your NeonGauge product to pin 1 of the Arduino and you are ready to go.
### Volume unit (VU) meter.
![alt text](https://github.com/SALTechips/NeonGauge/blob/master/extras/VU_Meter.gif)

This is a program in which the three neon tubes are used as a VU meter. Note that, for this application to work, the following are required:
* Winamp, available from [***here***](http://www.winamp.com/). The application was tested with Winamp v5.666.
* lcd_analyzer.ini (inside C:\)  found [***here***](https://github.com/SALTechips/NeonGauge/tree/master/extras). Open this file and chage the port name to the one your are using.
* gen_crownsoft_lcd.dll (inside C:\... Winamp\Plugins) found [***here***](https://github.com/SALTechips/NeonGauge/tree/master/extras).
* SoftwareSerial library, available from the LIbrary Manager (search for "SoftwareSerial"). The application was tested with SoftwareSerial v.1.0.0.
**Please note that you must first upload the sketch on the Arduino (with Winamp closed) and then open Winamp to play your songs. Moreover, in this example the Rx pin of NeonGauge product is connected to pin 11 (since this example uses SoftwareSerial) of the Arduino, but this is adjustable (refer to the sketch comments)**.

Many thanks to **Barreto Raul** for providing the lcd_analyzer.ini and gen_crownsoft_lcd.dll files.
## Authors
* **Platon Evangelos**
* **Tsekenis Alex**
## Licence
The NeonGauge library is licensed under the GNU General Public License (GPL) version 3, as published by the Free Software Foundation. Refer to the [***LICENSE***](https://github.com/SALTechips/NeonGauge/blob/master/LICENSE).
## Support
If you have any questions regarding the ***NeonGauge*** library or the product, please contact SALTechips [***here***](https://www.saltechips.com/contact/).
