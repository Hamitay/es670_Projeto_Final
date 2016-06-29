/**********************************************************************/
/* Projeto SHALOM                                                     */
/* Author: Lucas de Melo Manço                                        */
/* Last change: 28/06/2015                                            */
/* Brief: Código de controle do carrinho através da plataforma Arduino*/
/**********************************************************************/
#include <Servo.h>
#include <SoftwareSerial.h>

//Define os pinos para a serial   
SoftwareSerial BT(10, 11); // RX, TX

/*----Constant definitions----*/
#define INITAL_SERVO_ANGLE 101
#define FORWARD 1
#define BACKWARDS 0
#define CMD_MIN_LENGTH 11

/*------Global variables and objects------*/
String inString = "";    // string to hold input
int pwm_dc = 0;          // DC motor power
int dir = 0;             // H-bridge direction
int angle = 0;           // Servomotor angle
Servo servoDiant;        // Servomotor object
/*----------------------------------------*/

/*-----Pins definitions-------*/
int DC1 = 2;  // Forward
int DC2 = 3;  // Backward
int EN = 4;
int SERVO = 5;
/*----------------------------*/

void setup() {
  // Open serial communications and wait for port to open:
  BT.begin(38400);
  Serial.begin(9600);

  pinMode(DC1, OUTPUT);   // sets the pin as output
  pinMode(DC2, OUTPUT);   // sets the pin as output
  pinMode(EN, OUTPUT);
  servoDiant.attach(SERVO);
  servoDiant.write(INITAL_SERVO_ANGLE); //101 is the zero, 127 is the max for right and 75 is the max for left

  digitalWrite(EN, HIGH);
}


void readCommand(String cmd)
{
  /*Sanity Check*/
   if(cmd.equals(""))
    return;
  
  /*Get all the information from the command string*/
  String sangle = cmd.substring(0,4);
  String spower = cmd.substring(5,8);
  String sdir = cmd.substring(9,10);
  Serial.println(sangle);
  Serial.println(spower);
  Serial.println(sdir);
  
  /*Convert the information to integer*/
  /*With the integer information we can now change the power and direction of the DC motors and angle of the servomotor)*/
  angle = sangle.toInt();
  pwm_dc = spower.toInt();
  dir = sdir.toInt();
  //Serial.println(angle);
  //Serial.println(pwm_dc);
  //Serial.println(dir);
}

void setMotor()
{
  /*Converts power to 0-255*/
  int iConvertedPower = (float)(pwm_dc)*255/100;
  /*Writes power based on the direction the cart must go*/
  if(dir == FORWARD)
  {
    analogWrite(DC1,iConvertedPower);
    analogWrite(DC2,0);
  }else
  if(dir == BACKWARDS)
  {
    analogWrite(DC1,0);
    analogWrite(DC2,iConvertedPower); 
  }
}

void setServo()
{
  //First of all, we convert the angle to 75-127 range
  float iConvertedAngle = float((((float(angle)+180)/360)*52)+75);
  
  //Then we write the converted angle to the servo
  
  servoDiant.write(iConvertedAngle);
}


void loop() {

  if (BT.available()) 
  {  
     while(BT.available()) 
     { // While there is more to be read, keep reading.  
       inString += (char)BT.read();  
     }
  } 

   
  readCommand(inString);
  setServo();
  setMotor();
  inString = "";

}

