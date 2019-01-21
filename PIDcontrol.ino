//PIN DESIGNATIONS AND VARIABLE DECLARATIONS

//Sensor Board Pin Designations
 //Analog ins are for reading sensor values
 //Analog Out's are for controlling PWM indicator LEDs
const int analogInPin_0 = A0; // Analog input pin that the potentiometer is attached to
const int analogOutPin_0 = 2; // Analog output pin that the LED is attached to
const int analogInPin_1 = A1;
const int analogOutPin_1 = 4;
const int analogInPin_2 = A2;
const int analogOutPin_2 = 11;
const int analogInPin_3 = A3;
const int analogOutPin_3 = 12;
const int analogInPin_4 = A4;
const int analogOutPin_4 = 13;


//Pin Designations for Signal light LEDs
int LEDR = A5;
int LEDL = 3;


//Vars to store values read from sensor
int sensorValue_0 = 0;
int sensorValue_1 = 0;
int sensorValue_2 = 0;
int sensorValue_3 = 0;
int sensorValue_4 = 0;


//Vars to store PWM values that will control sensor indicator LEDs
int outputValue_0 = 0;
int outputValue_1 = 0;
int outputValue_2 = 0;
int outputValue_3 = 0;
int outputValue_4 = 0;

//Pin Designations for Motor
int ENABLEL = 5;
int FORWARDL = 6;
int BACKWARDL = 7;
int ENABLER = 8;
int FORWARDR = 10;
int BACKWARDR = 9;

//Is there tape at sensor? 1-> yes, 0-> no
int tapeStatus_0 = 0;
int tapeStatus_1 = 0;
int tapeStatus_2 = 0;
int tapeStatus_3 = 0;
int tapeStatus_4 = 0;

//Sensor values vary from sensor to sensor and from ambient lighting. Adjust these to compensate.
int sensorMin_0 = 0;
int sensorMax_0 = 550;
int sensorMin_1 = 0;
int sensorMax_1 = 800;
int sensorMin_2 = 0;
int sensorMax_2 = 800;
int sensorMin_3 = 0;
int sensorMax_3 = 700;
int sensorMin_4 = 0;
int sensorMax_4 = 700;

//Decimal form of binary number representing current readings from sensor
int arrayStatus = 0;

//Stores the previous direction the robot was moving. Used when robot loses sight of line.
int previousDirection = 0;

//Stores the error for use in PID control
int error = 0;
int PID = 0;
int Kp = 0;
int Proportional = 0;
int Ki = 0;
int Integral = 0;
int Kd = 0;
int Derivative = 0;
int previousError = 0;

//FUNCTION DECLARATIONS

//Decides whether the sensor is seeing tape or empty space
int tapeDiscriminator (int, int, int);

//Translates the binary form of the sensor readings to a decimal number
int encodeBinaryToDecimal (int,int,int,int,int);

//Function to activate and control motors
int drive(int myDirection, int mySpeed);

//Function to get the current Error for the PID controller
int getError(int,int,int,int,int);


void setup() {
Serial.begin(9600);// initialize serial communications at 9600 bps:
 
pinMode(ENABLEL,OUTPUT);
pinMode(FORWARDL,OUTPUT);
pinMode(BACKWARDL,OUTPUT);
pinMode(ENABLER,OUTPUT);
pinMode(FORWARDR,OUTPUT);
pinMode(BACKWARDR,OUTPUT);
pinMode(LEDR,OUTPUT);
pinMode(LEDL,OUTPUT);

 
//Motor test - moves robot forwards and backwards. Helpful for troubleshooting
digitalWrite(ENABLEL,HIGH);
analogWrite(FORWARDL,255);
digitalWrite(ENABLER,HIGH);
analogWrite(FORWARDR,255);
delay(500);
digitalWrite(ENABLEL,LOW);
analogWrite(FORWARDL,0);
digitalWrite(ENABLER,LOW);
analogWrite(FORWARDR,0);
delay(1000);
digitalWrite(ENABLEL,HIGH);
analogWrite(BACKWARDL,255);
digitalWrite(ENABLER,HIGH);
analogWrite(BACKWARDR,255);
delay(500);
digitalWrite(ENABLEL,LOW);
analogWrite(BACKWARDL,0);
digitalWrite(ENABLER,LOW);
analogWrite(BACKWARDR,0);
delay(1000);
}


void loop() {
// read the sensor analog in value:
sensorValue_0 = analogRead(analogInPin_0);
sensorValue_1 = analogRead(analogInPin_1);
sensorValue_2 = analogRead(analogInPin_2);
sensorValue_3 = analogRead(analogInPin_3);
sensorValue_4 = analogRead(analogInPin_4);


// map it to the range of the LED PWM analog out:
outputValue_0 = map(sensorValue_0, sensorMin_0, sensorMax_0, 0, 255);
outputValue_1 = map(sensorValue_1, sensorMin_1, sensorMax_1, 0, 255);
outputValue_2 = map(sensorValue_2, sensorMin_2, sensorMax_2, 0, 255);
outputValue_3 = map(sensorValue_3, sensorMin_3, sensorMax_3, 0, 255);
outputValue_4 = map(sensorValue_4, sensorMin_4, sensorMax_4, 0, 255);


// Write PWM value to LEDs. Brightness of LEDs corresponds to sensor reading
analogWrite(analogOutPin_0, outputValue_0);
analogWrite(analogOutPin_1, outputValue_1);
analogWrite(analogOutPin_2, outputValue_2);
analogWrite(analogOutPin_3, outputValue_3);
analogWrite(analogOutPin_4, outputValue_4);


// print the results to the serial monitor
Serial.print("sensor = " );
Serial.print(sensorValue_0);
Serial.print("    " );
Serial.print(sensorValue_1);
Serial.print("    " );
Serial.print(sensorValue_2);
Serial.print("    " );
Serial.print(sensorValue_3);
Serial.print("    " );
Serial.print(sensorValue_4);
Serial.print("    " );


Serial.print("output = ");
Serial.print(outputValue_0);
Serial.print("    " );
Serial.print(outputValue_1);
Serial.print("    " );
Serial.print(outputValue_2);
Serial.print("    " );
Serial.print(outputValue_3);
Serial.print("    " );
Serial.print(outputValue_4);
Serial.print("    " );
Serial.print("\n" );


//Decide whether sensor is seeing tape or not
tapeStatus_0 = tapeDiscriminator(sensorMin_0,sensorMax_0,sensorValue_0);
tapeStatus_1 = tapeDiscriminator(sensorMin_1,sensorMax_1,sensorValue_1);
tapeStatus_2 = tapeDiscriminator(sensorMin_2,sensorMax_2,sensorValue_2);
tapeStatus_3 = tapeDiscriminator(sensorMin_3,sensorMax_3,sensorValue_3);
tapeStatus_4 = tapeDiscriminator(sensorMin_4,sensorMax_4,sensorValue_4);


 
//PID Control
error=getError(tapeStatus_0,tapeStatus_1,tapeStatus_2,tapeStatus_3,tapeStatus_4);
Proportional = error;
Integral = Integral + error;
Derivative = error - previousError;
PID = (Kp*P) + (Ki*I) + (Kd*D);
previousError = error;

if (PID < 1){
 PID = PID*-1;
 drive (-1, map(PID, 0, 4, 0, 255));
}
else if(PID == 0){
 drive (1, map(PID, 0, 4, 0, 255));
}
else{
 drive (1, 255);
}
delay(2); // minimum wait time for analog PWM reader to reset in between readings
}



/*Function: tapeDiscriminator()
Purpose: decides whether sensor is reading tape or whitespace
Passed variables:
  myMin: sensor's custom minimum read value
  myMax: sensor's custom maximum read value
  sensorValue: Current value being read by sensor
Returns: boolean 1 or 0, 1-> tape, 0-> white space
*/
int tapeDiscriminator (int myMin, int myMax, int sensorValue){
  
  int threshold = (myMax-myMin)/2 + myMin;
  int myReturn;
  
  if (sensorValue >= threshold){
    myReturn = 1;
  }
  else{
    myReturn = 0;
  }

  return myReturn;
 }


/*Function: encodeBinaryToDecimal()
Purpose: Takes 5 boolean sensor read values, encodes them to a decimal number representing the 5-digit binary value of their state.
Passed variables:
  sensor_0 to sensor_4: the boolean tape status values corresponding to sensors 0 through 4
Returns: decimal value representing state of tape detection by sensor array
*/
int encodeBinaryToDecimal (int sensor_0,int sensor_1,int sensor_2, int sensor_3,int sensor_4){
  int myReturn = sensor_0*(2*2*2*2) + sensor_1*(2*2*2) + sensor_2*(2*2) + sensor_3*(2) + sensor_4;
  return myReturn;
}


/*Function: drive()
Purpose: Operates motor H-bridge
Passed variables:
  myDirection: The direction we wish to steer the car
  mySpeed: The PWM speed at which we wish to turn the wheels
Returns: myDirection (used for previous direction functionality)
*/
int drive(int myDirection, int mySpeed){
  // Direction: 0-> straight, 1-> right, -1-> left

  Serial.print("\n");
  Serial.print(myDirection);
  Serial.print("\n");
  if (myDirection == 0){
      digitalWrite(ENABLEL,HIGH);
      digitalWrite(ENABLER,HIGH);
      analogWrite(FORWARDL, mySpeed);
      analogWrite(FORWARDR, mySpeed);
      digitalWrite(LEDL,LOW);
      digitalWrite(LEDR,LOW);
  }
  if (myDirection == -1){
    //RIGHT -> activate left wheels
      digitalWrite(ENABLEL,LOW);
      digitalWrite(ENABLER,HIGH);
      digitalWrite(FORWARDL, LOW);
      analogWrite(FORWARDR, mySpeed);
      digitalWrite(LEDL,LOW);
      digitalWrite(LEDR,HIGH);
  }
  if (myDirection == 1){
    //LEFT -> activate right wheels
      digitalWrite(ENABLEL,HIGH);
      digitalWrite(ENABLER,LOW);
      analogWrite(FORWARDL, mySpeed);
      digitalWrite(FORWARDR, LOW);
      digitalWrite(LEDL,HIGH);
      digitalWrite(LEDR,LOW);
  }
  
 //sets polling rate of microcontroller, or (amount of thinking)/(distance travelled). 
 //Too Fast -> Robot shakes back and forth as if it has Parkinson's disease
 //Too Slow -> Robot doesnt respond to turns in time and runs off track
  delay (75); 
  return myDirection;
}

int getError( int sensor_0, int sensor_1, int sensor_2, int sensor_3, int sensor_4){
 int error = 0;
  if((sensor_0 == 0)&&(sensor_1 == 0)&&(sensor_2 == 0)&&(sensor_3 == 0)&&(sensor_4 == 1)){
   error = 4;
  }
  else if((sensor_0 == 0)&&(sensor_1 == 0)&&(sensor_2 == 0)&&(sensor_3 == 1)&&((sensor_4 == 1)){
   error = 3;
  }
  else if((sensor_0 == 0)&&(sensor_1 == 0)&&(sensor_2 == 0)&&(sensor_3 == 1)&&(sensor_4 == 1)){
   error = 2;
  }
  else if((sensor_0 == 0)&&(sensor_1 == 0)&&(sensor_2 == 1)&&(sensor_3 == 1)&&(sensor_4 == 0)){
   error = 1;
  }
  else if((sensor_0 == 0)&&(sensor_1 == 0)&&(sensor_2 == 1)&&(sensor_3 == 0)&&(sensor_4 == 0)){
   error = 0;
  }
  else if((sensor_0 == 0)&&(sensor_1 == 1)&&(sensor_2 == 1)&&(sensor_3 == 0)&&(sensor_4 == 0)){
   error =- 1;
  }
  else if((sensor_0 == 0)&&(sensor_1 == 1)&&(sensor_2 == 0)&&(sensor_3 == 0)&&(sensor_4 == 0)){
   error = -2;
  }
  else if((sensor_0 == 1)&&(sensor_1 == 1)&&(sensor_2 == 0)&&(sensor_3 == 0)&&(sensor_4 == 0)){
   error = -3;
  }
  else if((sensor_0 == 1)&&(sensor_1 == 0)&&(sensor_2 == 0)&&(sensor_3 == 0)&&(sensor_4 == 0)){
   error = -4;
  }
  return error;
}

