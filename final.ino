#include <Keypad.h> 
#include <Wire.h> 
#include <Servo.h>
#include <LiquidCrystal.h>   
#include <SoftwareSerial.h>
#define Password_Lenght 5           //Password Length not exceeding 4

SoftwareSerial mySerial(46, 44); // RX, TX
LiquidCrystal lcd(12,11,5,4,3,2);             //Arduino pins which are connected to LCD display
char Data[Password_Lenght]; // 4 is the number of chars it can hold + the null char = 5
//variable to store password
char Master[Password_Lenght] = "1234"; //Password for activating home security system="1234" 
byte data_count = 0;                   //Number of bytes in Data String(Input Password Length)
byte master_count = 0;                 //Number of bytes in Master String(Stored Password Length)
bool Pass_is_good;
char customKey;
int pos = 0; 
const byte ROWS = 4;                  //Number of rows in the Keypad
const byte COLS = 4;                  //Number of columns in the Keypad
char keys[ROWS][COLS] = {               
{'1', '2', '3', 'A'},
{'4', '5', '6', 'B'},
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};
Servo myservo;
//Setting rows and columns of Keypad
byte rowPins[ROWS] = { 53,51,49,47}; //connect to the row pinouts of the keypad
byte colPins[COLS] = { 45,43,41,39}; //connect to the column pinouts of the keypad
int val;
int tempPin = 1;
int g=0;

const int sensorPin= 0;
//const int buzzerPin= 13;
int smoke_level;
int u=0;
int shariq=0;                            
int flag=0;                         
//int ledPin = 13;                // choose the pin for the LED
int matlab = 28;                // choose the pin for the LED
int matlab1 = 26;                // choose the pin for the LED
int inputPin1 = 7;            // choose the input pin (for PIR sensor)
int inputPin2=6;                    //input Pin for PIR sensor 2(Room N0.2)
int inputPin3=50;                   //input Pin for PIR sensor 3(Room No.3)
int inputPin4=48;                   //input Pin for PIR sensor 4(Room No.4)
int pirState1 = LOW;             // we start, assuming no motion detected
int pirState2=LOW;               //Assuming no motion detected in Room No.2
int pirState3=LOW;               //Assuming no motion detected in Room No.3
int pirState4=LOW;              //Assuming no motion detected in Room No.4
//int val = 0;                    // variable for reading the pin status
int temp=0;
int pinSpeaker = 10;           //Set up a speaker on a PWM pin (digital 9, 10, or 11)
int redLed = 8;                //RED LED is connected to the processor's 8th PIN
int greenLed = 9;              //GREEN LED is connected to the processor's 9th PIN
int virat=0;                  //Counting the Number of Times we are entering the Password(It counts when we type the Password incorrectly)
int SendCount=0;


 int light=0;
  /********************************************/
Keypad customKeypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);
void kohli()
  {
    if(virat>=3)                            //If Number of tries is greater than or equal to 3  
    {
    //    SendCount=1;       

  // rambabu();
                          //function to make a call
    int gh;
   // gh=virat*5;
   lcd.setCursor(0,1);                      //Setting cursor to 0th column and 1st row 
  lcd.print("Try after ");                  //Printing "Try after 2 min" at (0,1) position on LCD display
  lcd.print("1");                           
  lcd.print(" min");
  delay(60000);                        // 1sec=1000milliseconds
  //delay=2*1000*60=2min
  //if Number of tries is greater than or equal to 3 then we provide a delay of 2minutes 
    }
    else
    {
      lcd.setCursor(0,2);                 //Setting cursor to 0th column and 2nd row
      lcd.print("Try Again");             //Printing "Try Again" if number of tries(virat) is less than 3
    }
      virat=virat+1;                     //Incrementing the Number of tries 
  }
  /*
  void loop6()
  {
       if(g==0&&SendCount==1)
  {
   switch('s')
  {
    case 's':
      SendMessage();
      g=1;
      break;
    case 'r':
      RecieveMessage();
      break;
 }
  }
  if (mySerial.available()>0)
   Serial.write(mySerial.read());
  
    
  }*/
void bad()
{ 
  lcd.setCursor(0,1);                   //Setting the cursor to 0th column and 1st row 
  lcd.print("Enter Password:-");        //printing("Enter Password:-")
  kohli();                              //kohli() Function is called and if Number of tries is less than 3 then the password is taken as input else it provides a delay of 2 minutes
}
void good()
{ lcd.setCursor(0,0);                   //Setting the cursor at 0th row and 0th column
  setup1();                             //If the input Password is correct then the Home Security system is activated
}
//*******************************^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^/
void setup1() {  pinMode(redLed, OUTPUT);      // declare LED as output  pinMode(inputPin, INPUT);     // declare sensor as input
  pinMode(pinSpeaker, OUTPUT);                  //Output state of the Buzzer
//  pinMode(ledPin,OUTPUT);                       //Output State of all LED's
  pinMode(greenLed,OUTPUT);                     //Output state of Green LED
  digitalWrite(matlab1,LOW);
  Serial.begin(9600);
  lcd.begin(20, 4);                              //
  lcd.setCursor(1, 0);                                            // Set LCD cursor position (column, row)
  lcd.print("HOME  SECURITY");                                      // Print text to LCD
  lcd.setCursor(5, 1);                                            // Set LCD cursor position (column,row) 
  lcd.print("SYSTEM");                                            // Print text to LCD
  delay(2000);                                                      // Delay to read text
lcd.clear();                                                    // Clear LCD    
lcd.setCursor(0, 0);                                            //Setting cursor at 0th row and 0th column 
      lcd.print("Processing Data.");                            
      delay(1000);
      lcd.clear(); 
      lcd.setCursor(0,0);
      lcd.print("System Activated.");
      delay(1000);   
      close1();
}
void loop1()                                      
{
  
  if(u==2)
  {
    lcd.clear();
   lcd.setCursor(5,0);
   lcd.print("ALERT!!!!!");
   lcd.setCursor(3,1);
   lcd.print("Enter Password");
   lcd.setCursor(3,2);
   lcd.print("to de-activate");
     u=0;
  }
  Serial.print("correct password");
 /* if(digitalRead(inputPin1)==HIGH)            //If the motion is detected in Room-1
  { //rambabu();
    lcd.clear();                              //Clears the LCD Dispaly screen
  //rambabu();
    digitalWrite(redLed,HIGH);                 //RED LED starts glowing
    digitalWrite(pinSpeaker,HIGH);             //Buzzer starts beeping
    digitalWrite(ledPin,HIGH);                 //LED strip starts glowing
    lcd.setCursor(0,0);                        //Cursor is set to 0th row and 0th column on the LCD display
    lcd.print("Motion in Bedroom");             //prints the text on the LCD display
      lcd.setCursor(3,1);  
      //Cursor is set to 3rd column and 1st row
    delay(1000);
    lcd.print("Enter Password");               //prints the Text("Enter Password") on the LCD display
    lcd.setCursor(3,2);                        //Cursor is set to 3rd column and 2nd row on the LCD Display
    lcd.print("to de-activate :-");            //Prints the Text("to de-activate :-") on the LCD display
                            //clears the LCD display screen
    u=2;
    
  }    
  if(digitalRead(inputPin2)==HIGH)            //If the motion is detected in Room-2
  { 
   //rambabu();
    lcd.clear();                              //Clears the LCD Dispaly screen
  //rambabu();
    digitalWrite(redLed,HIGH);                //RED LED starts glowing
    digitalWrite(pinSpeaker,HIGH);            //Buzzer starts beeping
    digitalWrite(ledPin,HIGH);                //LED strip starts glowing
    lcd.setCursor(0,0);                        //Cursor is set to 0th row and 0th column on the LCD display
    lcd.print("Motion in Kitchen");             //prints the text on the LCD display
      lcd.setCursor(3,1);                      //Cursor is set to 3rd column and 1st row
    delay(1000);
    lcd.print("Enter Password");               //prints the Text("Enter Password") on the LCD display

    lcd.setCursor(3,2);                        //Cursor is set to 3rd column and 2nd row on the LCD Display
    lcd.print("to de-activate :-");            //Prints the Text("to de-activate :-") on the LCD display
    //lcd.setCursor(4,3);
     //lcd.print("at time");
     //digitalClockDisplay();
     //lcd.clear();                             //clears the LCD display screen
    u=2;
    
  }*/
   if(digitalRead(inputPin3)==HIGH)                   //If the motion is detected in Room-3
  {
    //rambabu();
     lcd.clear();                                     //Clears the LCD Dispaly screen
      //rambabu();                    //rambabu() Function is called so that we can make a call to the user using GSM module 
    int vis=0;                                        
    digitalWrite(redLed,HIGH);                        //RED LED starts glowing
    //digitalWrite(pinSpeaker,HIGH);                    //Buzzer starts beeping
//    digitalWrite(ledPin,HIGH);                        //LED strip starts glowing
    lcd.setCursor(0,0);                        //Cursor is set to 0th row and 0th column on the LCD display
    lcd.print("Motion in Kitchen");             //prints the text on the LCD display
    delay(1000);
      lcd.setCursor(3,1);                      //Cursor is set to 3rd column and 1st row
    lcd.print("Enter Password");               //prints the Text("Enter Password") on the LCD display
    lcd.setCursor(3,2);                        //Cursor is set to 3rd column and 2nd row on the LCD Display
    lcd.print("to de-activate :-");            //Prints the Text("to de-activate :-") on the LCD display
                                 //clears the LCD display screen
    u=2;
  }
   if(digitalRead(inputPin4)==HIGH)                 //If the motion is detected in Room-4
  { 
   // rambabu();
    lcd.clear();                                    //Clears the LCD Dispaly screen   
                                      //rambabu() Function is called so that we can make a call to the user using GSM module 
    digitalWrite(redLed,HIGH);                      //RED LED starts glowing
   // digitalWrite(pinSpeaker,HIGH);                  //Buzzer starts beeping
//    digitalWrite(ledPin,HIGH);                      //LED strip starts glowing
    lcd.setCursor(0,0);                        //Cursor is set to 0th row and 0th column on the LCD display
    lcd.print("Motion in Hall");             //prints the text on the LCD display
    lcd.setCursor(3,1);
    //Cursor is set to 3rd column and 1st row
    delay(1000);
    lcd.print("Enter Password");               //prints the Text("Enter Password") on the LCD display
    lcd.setCursor(3,2);                        //Cursor is set to 3rd column and 2nd row on the LCD Display
    lcd.print("to de-activate :-");            //Prints the Text("to de-activate :-") on the LCD display
  //   lcd.clear();                             //clears the LCD display screen
    u=2;
    }
    int gh;
  gh=1;
  customKey = customKeypad.getKey();          

  if (customKey)
  {
    if(light==0)
    lcd.clear();
     lcd.setCursor(5,0);
   
   lcd.print("ALERT!!!!!");
   lcd.setCursor(3,1);
   lcd.print("Enter Password");
   lcd.setCursor(3,2);
   lcd.print("to de-activate :-");
   light=1;
    Data[data_count] = customKey; // store char into data array
    lcd.setCursor(data_count,3); // move cursor to show each new char
    lcd.print("*"); // print char at said cursor
    data_count++; // increment data array by 1 to store new char, also keep track of the number of chars entered
  }
  if(data_count == Password_Lenght-1) // if the array index is equal to the number of expected chars, compare data to master
  {
    if(!strcmp(Data, Master))// equal to (strcmp(Data, Master) == 0)
    //if the input Password is same as the stored Password then the Home Security System deactivates
    {
        //   digitalWrite(matlab,LOW);  
      digitalWrite(redLed,LOW);               //RED LED stops glowing
      digitalWrite(greenLed,HIGH);            //Green LED starts glowing
      digitalWrite(matlab,LOW);
//      digitalWrite(ledPin,LOW);               //LED strip stops glowing                 
      digitalWrite(pinSpeaker,LOW);           //Buzzer stops Beeping
      lcd.clear();                            //clears the LCD Display screen
      lcd.setCursor(0,0);                     //Cursor is set to 0th row and 0th column on the LCD display
      lcd.print("System deactivated");        //Prints the text on the LCD Display
      digitalWrite(matlab1,HIGH);
      delay(3000);
      clearData();
      lcd.clear();
      loop();
      return;
    }
    else
    //if the entered Password is wrong then this loop executes
    { 
      lcd.clear();                        //clears the LCD Display Screen
      lcd.setCursor(0,0);                 //Cursor is set to 0th row and 0th column
      bad();                              //bad() Function is called to re-enter the Password 
      //If Number of tries is less than 3 we can enter the Password else we want to wait for 2min
      clearData();
    }
  }
  
  loop1();
}
// duration in mSecs, frequency in hertz
void playTone(long duration, int freq) {
    duration *= 1000;
    int period = (1.0 / freq) * 1000000;
    long elapsed_time = 0;
    while (elapsed_time < duration) {
        digitalWrite(pinSpeaker,HIGH);
        delayMicroseconds(period / 2);
        digitalWrite(pinSpeaker, LOW);
        delayMicroseconds(period / 2);
        elapsed_time += (period);
    }
}
void setup()
{
digitalWrite(matlab1,LOW);
  digitalWrite(matlab,LOW);  
  pinMode(sensorPin, INPUT);//the smoke sensor will be an input to the arduino
  lcd.begin(20,4);              //Initialising Number of rows and columns in LCD Display
  //Number of rows=4
  //Number of columns=20
  lcd.clear();                  //Clears the LCD display Screen
  //lcd.setCursor(10,3);
  //digitalClockDisplay();
int pirState1 = LOW;             // we start, assuming no motion detected
int pirState2=LOW;               //Assuming no motion detected in Room No.2
int pirState3=LOW;               //Assuming no motion detected in Room No.3
int pirState4=LOW;
//myservo.attach(22);
}

void loop()
{
  digitalWrite(matlab1,LOW);
     if(digitalRead(matlab)==HIGH)
   {
    good();    
    loop1();
   }
  digitalWrite(greenLed,HIGH);                        //Green LED starts glowing
  digitalWrite(redLed,LOW);                           //Initially RED LED is at off state
//  digitalWrite(ledPin,LOW);                           //Initially LED strip is at off state
  digitalWrite(pinSpeaker,LOW);                       //Initially Buzzer is at low state(if motion is detected in any of the rooms then Buzzer starts beeping
  lcd.setCursor(0,0);                                 //Cursor is set to 0th row and 0th column on the LCD Display
 // lcd.clear();
  lcd.print("HOME SECURITY SYSTEM");
  lcd.setCursor(0,1);
  lcd.print("Enter password:-");
 lcd.setCursor(12,2);
lcd.print("13/11/16");
  u=0;
  customKey = customKeypad.getKey();                  
  if (customKey)  
  { 
    Data[data_count] = customKey; // store char into data array
    lcd.setCursor(data_count,2); // move cursor to show each new char
    lcd.print("*"); // prints "*" inplace of the input integer
    data_count++; // increment data array by 1 to store new char, also keep track of the number of chars entered
  }

  if(data_count == Password_Lenght-1)          
  //if the length of the input Password and stored Password are same then it checks whether the input Password is correct or not
  {
    lcd.clear();                                    //clears the LCD Display screen
    lcd.setCursor(0, 0);                            //cursor is set to 0th row and 0th column

    if(strcmp(Data, Master)==0)                     //if input Password and stored Password are same then the Home Securty System activates
    { data_count=0;                                 //Initialising the length of input Password to 0
      digitalWrite(redLed,HIGH);                    //RED LED starts glowing
      digitalWrite(greenLed,LOW);                   //GREEN LED stops glowing
      good();                                       //good() Function is called to activate the Home Security system
      u=1;
      loop1();
      return;
    }
    else
    { 
      bad();                                        //if the input Password and stored Password are different then the bad() Function is called
      //In bad() function if the Number of tries is less than 3 then we can re-enter the Password 
      //if Number of tries is greater than 3 then a delay of 2min is provided
    }
    delay(1000);
    lcd.clear();
    clearData();                                  //clearData() Function is used to clear the Data string where input Password is stored
  }
}

void clearData()
//This loop is used to clear the Data string where input Password is stored 
{
  while(data_count !=0)                          
  {    
    Data[data_count--] = 0;                       //Setting all the elements of the Data Array to 0
  }
  return;
}
/*
void printDigits(byte digits){
    if(digits < 10)
        lcd.print('0');
    lcd.print(digits);
}
*/
void rambabu()
{
Serial.println("Calling through GSM Modem");


mySerial.begin(9600);
delay(2000);
mySerial.println("ATD +919703082680;"); // ATDxxxxxxxxxx; -- watch out here for semicolon at the end!!

// print response over serial port
if (mySerial.available())
Serial.write(mySerial.read());
}

void open1()
{
//  SendMessage();
  for (pos = 0; pos <= 120; pos += 1) 
  {
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15ms for the servo to reach the position
  }
  return;
}

void close1()
{
 // SendMessage1();
    for (pos = 60; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15ms for the servo to reach the position
  return;
}
}
/* void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919542758199\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("I am SMS from GSM Module");// The SMS text you want to send
//  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}



 void RecieveMessage()
{
  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to recieve a live SMS
  delay(1000);
 }
 */
