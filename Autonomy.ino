
//the right motor will be controlled by the motor A pins on the motor driver
const int AIN1 = 13;           //control pin 1 on the motor driver for the right motor
const int AIN2 = 12;            //control pin 2 on the motor driver for the right motor
const int PWMA = 11;            //speed control pin on the motor driver for the right motor

//the left motor will be controlled by the motor B pins on the motor driver
const int PWMB = 10.;           //speed control pin on the motor driver for the left motor
const int BIN2 = 9;           //control pin 2 on the motor driver for the left motor
const int BIN1 = 8;           //control pin 1 on the motor driver for the left motor


//distance variables
const int trigPin = 7;
const int echoPin = 6;

//right distance variables
const int RtrigPin = 5;
const int RechoPin = 4;

//left distance variables
const int LtrigPin = 3;
const int LechoPin=2;

int switchPin = 0;             //switch to turn the robot on and off
int redButton = SCL; 

boolean Start=true;  
  int i=0; 

float distance = 0;            //variable to store the distance measured by the distance sensor
float Rdistance=0;
float Ldistance=0;

//robot behaviour variables
int backupTime = 300;           //amount of time that the robot will back up when it senses an object
int turnTime = 200;             //amount that the robot will turn once it has backed up

const double carpetLeft=250*(.65);
const double carpetRight=255*(.65);


/********************************************************************************/
void setup()
{
  pinMode(trigPin, OUTPUT);       //this pin will send ultrasonic pulses out from the distance sensor
  pinMode(echoPin, INPUT);        //this pin will sense when the pulses reflect back to the distance sensor

//Right Distance Sensor
 pinMode(RtrigPin, OUTPUT);       //this pin will send ultrasonic pulses out from the distance sensor
 pinMode(RechoPin, INPUT);        //this pin will sense when the pulses reflect back to the distance sensor
//Left Distance Sensor

 pinMode(LtrigPin, OUTPUT);       //this pin will send ultrasonic pulses out from the distance sensor
 pinMode(LechoPin, INPUT);        //this pin will sense when the pulses reflect back to the distance sensor

  pinMode(switchPin, INPUT_PULLUP);   //set this as a pullup to sense whether the switch is flipped
pinMode(redButton, INPUT_PULLUP);

  //set the motor control pins as outputs
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);

 Serial.begin(9600);                       //begin serial communication with the computer
  Serial.print("begin");  //test the serial connection
}

/********************************************************************************/
void loop()
{

  
  //DETECT THE DISTANCE READ BY THE DISTANCE SENSOR
  distance = getDistance();
Rdistance= RgetDistance();
Ldistance= LgetDistance();

  Serial.print("Front Distance: ");
  Serial.print(distance);
   Serial.print(" Left Distance: ");
  Serial.print(Ldistance);
   Serial.print(" Right Distance: ");
   Serial.print(Rdistance);
  Serial.println(" ");              // print the units
if(digitalRead(redButton) == LOW)
{

  i++;
  if (i%2==0)
  {
     Start= false;
  }
  else
  {
    Start=true;
  }
 
}
if(digitalRead(switchPin) )
  {  //if the on switch is flipped

    while (Rdistance<10)
    {
   //turn away from obstacle 
      //rightMotor(150);
    //  leftMotor(-50); 
    rightMotor(carpetRight + (255/(4*Rdistance)));
      Serial.println(carpetRight + (255/(4*Rdistance)));
       leftMotor(100); 
       delay(50);  
      Rdistance= RgetDistance();
    //  delay(150);
      Serial.println("Moving Left");
       
    }
    
    while (Ldistance<10)
      {
      
     //  leftMotor(235);
     //  rightMotor(100);
      leftMotor( carpetLeft + (255/(4*Ldistance)));
       rightMotor(100); 
       delay(50);  
      Ldistance= LgetDistance();
   
   //turn away from obstacle 
     //rightMotor(250+Ldistance*15);
    // leftMotor(235-Ldistance*15);    
     Serial.println("Moving Right");
    // delay(170);
      
     }
      
    if(distance < 10 )
    {   
     
      Serial.print(" ");
      Serial.print("BACK!");

      //stop for a moment
      rightMotor(0);
      leftMotor(0);
      delay(400);

      //back up
      rightMotor(-230);
      leftMotor(-200);
      delay(400);
      rightMotor(0);
      leftMotor(0);
      delay(500);
      
      Ldistance= LgetDistance();
      Rdistance= RgetDistance();
       if(Ldistance<Rdistance)
       {
        //turn right
       leftMotor(255);
       rightMotor(0);
       delay(200);
       }
       if(Rdistance<Ldistance)
       {
        leftMotor(0);
        rightMotor(255);
        delay(150);
       }
      
     
 
    }
else
{                         //if no obstacle is detected drive forward
      Serial.print(" ");
     Serial.print("Moving...");
    
   rightMotor(carpetRight-10);
      leftMotor(carpetLeft+3);
    }

  } 

  
  else
  {                         //if the switch is off then stop
 //stop the motors
      rightMotor(0);
      leftMotor(0);
  }

     //delay(20);
     //wait 50 milliseconds between readings
}

/********************************************************************************/
void rightMotor(int motorSpeed)                       //function for driving the right motor
{
  if (motorSpeed > 0)                                 //if the motor should drive forward (positive speed)
  {
    digitalWrite(AIN1, HIGH);                         //set pin 1 to high
    digitalWrite(AIN2, LOW);                          //set pin 2 to low
  }
  else if (motorSpeed < 0)                            //if the motor should drive backward (negative speed)
  {
    digitalWrite(AIN1, LOW);                          //set pin 1 to low
    digitalWrite(AIN2, HIGH);                         //set pin 2 to high
  }
  else                                                //if the motor should stop
  {
    digitalWrite(AIN1, LOW);                          //set pin 1 to low
    digitalWrite(AIN2, LOW);                          //set pin 2 to low
  }
  analogWrite(PWMA, abs(motorSpeed));                 //now that the motor direction is set, drive it at the entered speed
}

/********************************************************************************/
void leftMotor(int motorSpeed)                        //function for driving the left motor
{
  if (motorSpeed > 0)                                 //if the motor should drive forward (positive speed)
  {
    digitalWrite(BIN1, HIGH);                         //set pin 1 to high
    digitalWrite(BIN2, LOW);                          //set pin 2 to low
  }
  else if (motorSpeed < 0)                            //if the motor should drive backward (negative speed)
  {
    digitalWrite(BIN1, LOW);                          //set pin 1 to low
    digitalWrite(BIN2, HIGH);                         //set pin 2 to high
  }
  else                                                //if the motor should stop
  {
    digitalWrite(BIN1, LOW);                          //set pin 1 to low
    digitalWrite(BIN2, LOW);                          //set pin 2 to low
  }
  analogWrite(PWMB, abs(motorSpeed));                 //now that the motor direction is set, drive it at the entered speed
}

/********************************************************************************/
//RETURNS THE DISTANCE MEASURED 

float getDistance()
{
  float echoTime;                   //variable to store the time it takes for a ping to bounce off an object
  float calculatedDistance;         //variable to store the distance calculated from the echo time
  //send out an ultrasonic pulse that's 10ms long
  digitalWrite(trigPin, HIGH);

  digitalWrite(trigPin, LOW);
  echoTime = pulseIn(echoPin, HIGH);      //use the pulsein command to see how long it takes for the
                                          //pulse to bounce back to the sensor
  calculatedDistance = echoTime / 148.0;  //calculate the distance of the object that reflected the pulse (half the bounce time multiplied by the speed of sound)

  return calculatedDistance;              //send back the distance that was calculated
}

float RgetDistance()
{
  float RechoTime;
  float RcalculatedDistance;
  //send out an ultrasonic pulse that's 10ms long
  digitalWrite(RtrigPin, HIGH);

  digitalWrite(RtrigPin, LOW);

  RechoTime = pulseIn(RechoPin, HIGH);      //use the pulsein command to see how long it takes for the
                                          //pulse to bounce back to the sensor
  RcalculatedDistance = RechoTime / 148.0;  //calculate the distance of the object that reflected the pulse (half the bounce time multiplied by the speed of sound)
  return RcalculatedDistance;              //send back the distance that was calculated

}

float LgetDistance()
{
  float LechoTime;
  float LcalculatedDistance;
  //send out an ultrasonic pulse that's 10ms long
  digitalWrite(LtrigPin, HIGH);

  digitalWrite(LtrigPin, LOW);

  LechoTime = pulseIn(LechoPin, HIGH);      //use the pulsein command to see how long it takes for the
                                          //pulse to bounce back to the sensor
  LcalculatedDistance = LechoTime / 148.0;  //calculate the distance of the object that reflected the pulse (half the bounce time multiplied by the speed of sound)
  return LcalculatedDistance;              //send back the distance that was calculated

}
/********************************************************************************/
//RETURNS THE DISTANCE MEASURED FOR RIGHT SENSOR
