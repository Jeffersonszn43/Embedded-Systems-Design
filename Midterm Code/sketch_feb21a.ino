/*
Embedded System Midterm for Classes CDA4630 and CDA6316
Based on ESP32 technology, NodeMCU-32S
Dr. Bassem Alhalabi
Florida Atlantic Univercity, Boca Raton
Update: 2023-09-28
*/

/*
Updated by: Jefferson Charles
Date: 2/29/24
*/

// include files
#include <ESP32_Servo.h>

// class obects
Servo myservo;  // using class servo to create servo object, myservo, to control a servo motor
// Download the library from: https://github.com/jkb-git/ESP32Servo (Press on Code, and download as zip).
// Unzip and rename the folder to ESP32Servo.
// Put the folder in Document>Arduino>libraries


// ---------- defining pins for inputs 
const int servoPin = 23;      // servo GPIO pin
const int distPin = 35;         // ir GPIO analog pin
const int lightPin = 36;      // light sensor GPIO pin
const int touchPin = 34;      // touch sensor GPIO pin
const int tempPin = 39;       // temperature sensor GPIO pin

// ---------- defining pins for outputs 
const int touchLed = 25;      // touch green led
const int lightLed = 32;      // ligh blue led
const int lightPwmLed = 22;   // light yellow led - pwm
const int tempLed = 33;       // temperature red led

//  ---------- sensor values
int touchVal = 0, baseTouchVal=0;
int lightVal = 0, baseLightVal = 0, pwmVal = 0, mapPwmVal = 0;
int tempVal = 0, baseTempVal = 0;
int distVal = 0, baseDistVal = 0, mapDistVal = 0;
int flag = 0;


// ---------- Main functions 

// setup function: init all connections
void setup() 
{
  // Set up ADC resolution to 10 bits: will get values between 0-1024
  analogReadResolution(10);  
  // connect servo myservo to servoPin
  myservo.attach(servoPin);
  
  // set up analog pin as inputs
  pinMode(distPin, INPUT);
  pinMode(lightPin, INPUT);
  pinMode(touchPin, INPUT);
  pinMode(tempPin, INPUT);

  // set output pins
  pinMode(touchLed, OUTPUT);
  pinMode(lightLed, OUTPUT);
  pinMode(tempLed, OUTPUT);
  pinMode(lightPwmLed, OUTPUT);
 
  // set up default values
  digitalWrite(touchLed, HIGH);
  digitalWrite(lightLed, HIGH);
  digitalWrite(tempLed, HIGH);
  digitalWrite(lightPwmLed, HIGH);
  delay(1000);  // wait for 1000 ms

  myservo.write (180);
  delay(1000);  // wait for 1000 ms
  myservo.write (0);
  delay(1000);  // wait for 1000 ms

  digitalWrite(touchLed, LOW);
  digitalWrite(lightLed, LOW);
  digitalWrite(tempLed, LOW);
  digitalWrite(lightPwmLed, LOW);
  delay(1000);  // wait for 1000 ms


  // start the serial port
  Serial.begin(115200);

  // read sensors values and save them as baseline values
  baseLightVal = analogRead(lightPin);  // room light
  baseTempVal =  analogRead(tempPin);   // room temperature
  baseTouchVal = analogRead(touchPin);  // room touch
  baseDistVal = analogRead(distPin);  // room touch
}

void loop() 
{
  // ---------- distance sensor controls
  // read the distance sensor, set the min/max limits, and map to full range 0-180 
  //Here is an if statement that will allow the servo motor to be at it's max position as you quickly move your hand over the distance sensor.
  if (distVal >= 250 || distVal <= 1000)  
  {
    distVal = analogRead(distPin);  // 0 - 1023
    distVal = min (distVal, 1000);
    distVal = max (distVal, 250);
    mapDistVal = map (distVal, 250, 1000, 0, 180);  // map values between in range (250, 1010) to values in range (0, 180)
    //myservo.write (mapDistVal);

    // Here is a variable to be used to keep the position of the servo to its max position.
    int lastPosition = 0;
    // Here this if statement is saying that if the value of the servo does not equal the last position then have the value be the last position so that 
    // the servo will stop at that last position when you move your hand away quickly horizontally.
    if (mapDistVal != lastPosition)
    {
      myservo.write (mapDistVal);
      lastPosition = mapDistVal;
    }
  }  


  // ********** requirement # 1
  // the code above causes the servo to sweep from 0-90 as the distVal sweeps from 250-1000 as you vertically move your hand up/down over the distance sensor
  // modify the code so that if you move your hand horizantally quickly the servo stops in its last position
  /* enter your comments here:
  I created a if statement that if the distVal is between the min and the max range, then the distance sensor will start moving the servo between 0 to 90 degrees. I also added
  inside the if statement another if statement that will keep the servo in the last position its in when you quickly move your hand horizontally away. 
  */


  // ---------- light sensor controls
  // read light sensor
  lightVal = analogRead(lightPin);  // light sensor
  // The following two lines designate a deadzone band for the blue led between .3 and .5 of the baseLightVal for no change.
  if ((lightVal > (baseLightVal - (0.3 * baseLightVal)))) 
  { 
    digitalWrite(lightLed, HIGH); // if val above thresh (30% below room light)
  }  
  else if ((lightVal < (baseLightVal - (0.5 * baseLightVal)))) 
  { 
    digitalWrite(lightLed, LOW);  // if val under thresh (50% below room light)
  }  
  // observe when the blue led turns off and on as you move your finger up and down above the light sensor

  // ********** requirement #2
  // change the code above to expand the range from 0.3-0.5 to the max and explore the changes. 
  /* enter your comments here:
  When I expand the range of the deadzones of the light sensor, the blue led stays on when I apply darkness to the light sensor. But the yellow LED still goes dim after applying darkness.
  */

  // ---------- pwm controls for the yellow led, where led dims from 100% to 0% based on the light value
  pwmVal =lightVal;                         // copy the light val
  pwmVal = min(pwmVal, baseLightVal);  // allow pwmVal value to be max at room light
  pwmVal = max(pwmVal, 100);            // allow pwmVal value to be min is 10
  mapPwmVal = map(pwmVal, 100, baseLightVal, 245, 10);
  analogWrite(lightPwmLed, mapPwmVal);

  // ********** requirement #3
  // modify the code above to reverse the effect of dimming, that is when you cover the light sensors the yellow led should be bright
  /* enter your comments here:
  Switching the values 245 and 10 will reverse the effect of dimming when you apply darkness to the light sensor.
  */

  
  // ---------- touch sensor controls
  // read the touch sensor, and if touched, turn on the green led, when no touch turn led off
  //Below will be the variable that will be the baseline value.
  const int baselineVal = 1000;
  int threshold;
  touchVal = analogRead(touchPin);

  //Here we are calculating the threshold that will be a percentage of the baseline value.
  //we are doing 90% of the baseline.
  threshold = baselineVal * 0.9; 
  if (touchVal < threshold) 
  { 
   digitalWrite(touchLed, HIGH); // if touched, turn green LED on
  }              
  else                            
  { 
   digitalWrite(touchLed, LOW);  // not touched, so turn green LED off
  }


  // ********** requirement #4
  // the code above uses an absolute value to detect touching which may not be suitable for your skin
  // change that value to a percentage of the baseline value based on the actual reading when you touch
   /* enter your comments here:
   I created a basline value variable that will be used to calculate a threshold value that will be used in the if/else statement to see if the touch sensor is touched or not to light up the green LED.
  */

  
  // ---------- touch sensor controls
  // read the touch sensor, and if touched, turn on the green led, when no touch turn led off
  //Below will be the variable that will be the baseline value.
  //const int baselineVal = 1000;
  //int threshold;
  //touchVal = analogRead(touchPin);

  //Here we are calculating the threshold that will be a percentage of the baseline value.
  //we are doing 90% of the baseline.
  //threshold = baselineVal * 0.9; 
  if (touchVal < threshold) 
  {
    // Here is where we are going to toggle the green LED when we touch the touch sensor
    if (flag == 0)
    {
      flag = 1;  // Here is where we are setting the flag to 1 to show that the green LED is on
    }
    else
    {
      flag = 0; // Here is where we are setting the flag to 0 to show that the green LED is off
    }
    digitalWrite(touchLed, flag);  // Here is where we are setting the state of the LED using the flag
  }

  // ********** requirement #5
  // change the code so that every time you touch, the led will toggle, and when you untouch, led stays the same. hint: use a flag
  /* enter your comments here:
   I used a flag that will be used in an if/else statement that will be used to toggle the green LED when you touch on the touch sensor. The flag will be set to 1 to show that the green LED is on.
   The flag will be set to 0 to show that the green LED is off.
  */

 
  // ---------- temperature sensor controls
  // read the temp sensor, and if temp higher than the baseline, turn red led on, else turn led off
  // you can increase the sensor temp by touching/squeezing it between your thumb and index finger
  tempVal = analogRead(tempPin);  // temperature sensor
  if (tempVal >= baseTempVal * 1.03) // Here is where I did my upperbound for the temperature to where if the temperature exceeds above the baseline * the deadzone, then the red LED turns on
  { 
    digitalWrite(tempLed, HIGH);  
  } 
  else if (tempVal < baseTempVal * 1.03) // Here is where I did my lowerbound, which is basically saying if the temperature is lower than the baseline * the deadzone, then the red LED turns off
  { 
    digitalWrite(tempLed, LOW);   
  }
  // if you have skin temperature that is less than the room basline temp, the led will not turn on
  // in this case you need to change the code so that if the temperature is higher/lower than the baseline, the led will turn on

  // ********** requirement #6 
  // change the code and apply the deadzone band concept instead of threshold value, so that the led will stop flickering 
  /* enter your comments here:
  I created a deadzone value that will be around the baseline temperature value. I also created an upper and lower bound for the deadzone value.
  if the temprature is higher than or equal to the upper bound, then the red LED will turn on. If the temperature is lower that the lower bound, then the red LED will turn off.
  */



  // ---------- printing on serial monitor
  Serial.print("Dist  base value:  "); Serial.print(baseDistVal);   Serial.print("  Dist map value: "); Serial.println(distVal);
  Serial.print("light base value:  "); Serial.print(baseLightVal);  Serial.print("  light  Reading: "); Serial.println(lightVal); 
  Serial.print("light  PWD Value:  "); Serial.print(pwmVal);        Serial.print("  map  PWD Value: "); Serial.println(mapPwmVal);
  Serial.print("Touch base value: "); Serial.print(baseTouchVal);   Serial.print("  Touch  Reading: "); Serial.println(touchVal);
  Serial.print("Temp  base value:  "); Serial.print(baseTempVal);   Serial.print("  Temp   Reading: "); Serial.println(tempVal);



  // ---------- the mian loop dealy
  // here we are usning a loop delay to slow down the update rate of the analog input
  delay(100);  // wait for 100ms, the infinite loop interval 

  // ********** requirement #7
  // change the delay value (10, 100, 500 1000), and state you observation on the various loop delays
  /* enter your comments here:
   When the loop delay is 10ms, the components on the board read their analog inputs at a quicker rate.
   At a 100 ms, the rate at which the components read their analog inputs is at a normal rate.
   At 500 ms, the rate at which the components read their analog inputs is slow.
   Lastly at 1000ms, the rate at which the components read their analog inputs is really slow.
   So the higher in ms the delay, the slower the components read their analog inputs. The smalller the in ms the delay, the faster the components read their analog inputs.
  */


}
