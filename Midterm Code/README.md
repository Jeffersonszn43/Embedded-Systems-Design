## Midterm Project
#### For the midterm project, we had to create a circuit on a breadboard that has a touch sensor, a light sensor, temperature sensor, distance sensor, an SG90 micro servo motor, and the ESP32 Wroom 32 board. The outputs of each of these sensors will be shown through 4 LEDs (a green, yellow, blue, and red LED). Once the circuit was built on the breadboard, the skeleton code had to be tested with each of the sensors on the board to make sure the circuit was wired correctly. The project had 6 different requirements for each of the sensors and one requirement to observe the loop delay for each of the analog inputs of the components from the project. The goal of the project was to first have the circuit work using the skeleton code and when each of the components worked, you had to modify the code to satisfy the 7 different requirements for the project. Here are the 7 requirements for the project:

### 1. Distance Sensor:

- Originally, the distance sensor worked to where every time you hovered your hand over the distance sensor, the servo motor would move between 0 to 90 degrees depending on how close your hand is to the distance sensor. The closer you bring your hand to the distance sensor, the closer the servo motor will turn to 90 degrees. The first requirement of the project was to have the servo motor stay in it's last position when you bring your hand close to the distance sensor and quicky move it away horizonatally. 

### 2. Light Sensor:

- The light sensor worked to where every time you apply darkness to the light sensor, the blue LED turns on and the yellow LED gets dimmer. The 2nd requirement of the project was to keep expanding the threshold of the range of the light sensor and explore the changes that happens everytime you keep expanding the range. The 3rd requirement was to reverse the effect of dimming on the yellow LED everytime you apply darkness to the light sensor.

### 3. Touch Sensor:

- The touch sensor workes to where every time you touched the touch sensor, the green LED turns on. The 4th requirement of the project was to modify the touch sensor to where every you touched the touch sensor the green LED turns on and off. The 5th requirement was to modify the touch sensor to toggle the green LED upon touching the touch sensor.

### 4. Temperature Sensor:

- The temperature sensor works to where when you touch the temperature sensor, the red LED turns on when the tmperature of the sensor reaches above a certain threshold value. The red LED would flicker when the temperature would reach above that threshold value. The 6th requirement of the project was to modify the temperature sensor to apply deadzones to the upper and lower bounds of the sensor so that the red LED would not flicker when it comes on and turns off. 

### 5. Loop Delay:

- This requirement was to take the 100 ms loop delay and test the delay of 10, 100, 500, and 1000 ms and observe the different loop delays. The higher in ms the delay, the slower the components read their analog inputs. The smalller the in ms the delay, the faster the components read their analog inputs.

## Components Used
#### Here is a list of the components that were used in the project:
##### - ESP32-Wroom-32 Board
##### - One BC516 Touch Sensor
##### - One photoresistor 
##### - One LM34 Temperature Sensor
##### - One 2Y0A21 Distance Sensor
##### - One SG90 Micro Servo Motor
##### - One 0.1 uF Capacitor
##### - One 100 uF Capacitor
##### - One 3.3k Resistor
##### - One 100k Resistor
##### - Four 330 Ohm Resistors
##### - Two stripped wires for the touch sensor
##### - 8 male-to-female wires
##### - 6 Assorted wires
##### - One Green LED
##### - One Red LED
##### - One Blue LED
##### - One Yellow LED

- Here is a video that shows a demo of the midterm project: https://youtu.be/ADM_uNxHxt0?si=r8oWLH7FcSiBsdF3


