#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); 


// defines pins numbers for HC04
const int trigPin = 5;  //D?
const int echoPin = 6;  //D?



// defines variables for HC04 Signal
long duration;
int distance;

// defines variables for temperature and gas Signal
float gas;
float temp;

//define LED
  const int RED = 8;
  const int BLU = 10; 
  const int GRE = 9;
  const int YEL = 11;

  //define BUZ and PUMP
  const int BUZ = 7;
  const int MQ = 4;
  const int PUMP = 3;

void setup() {

  //iniate LCD
//  Wire.begin(2,0);
  lcd.init();                 //Init the LCD
  lcd.backlight();            //Activate backlight     
  lcd.home();

  //initiate HC04
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(RED, OUTPUT);
  pinMode(BLU, OUTPUT);
  pinMode(GRE, OUTPUT);
  pinMode(YEL, OUTPUT);
  pinMode(BUZ, OUTPUT);
  pinMode(MQ, INPUT);
  pinMode(PUMP, OUTPUT);
  Serial.begin(9600); // Starts the serial communication

  //initiate Gas sensor
}

void loop() {
  lcd.clear();
  lcd.print("Drainage Cleaner");
  delay(1000);
  

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;


  //Read Gas and Temp sensor
  float g = analogRead(A0);
  float t = analogRead(A0);
  gas =(g/1023)*100;
  temp =(t/1023)*500;


  Serial.print("Temp:");
  Serial.print("\t");
  Serial.print(temp);
  Serial.println();
  Serial.print("Gas:");
  Serial.print("\t");
  Serial.print(gas);
  Serial.println();
  Serial.print("Dist: ");
  Serial.print("\t");
  Serial.println(distance);
  Serial.println();

  //LCD display
  lcd.setCursor(0,1);
  lcd.print("Level");
  lcd.setCursor(0,8);
  lcd.print(distance);
  lcd.setCursor(0,11);
  lcd.print(gas);
  lcd.print("o");
  lcd.setCursor(0,14);
  lcd.print(temp);
  lcd.print("c");
  lcd.setCursor(1,1);
  if(distance<200){
    lcd.print("High Clog Level");
    digitalWrite(RED,HIGH);
    digitalWrite(BUZ,HIGH);
    digitalWrite(PUMP,HIGH);
    }
    else if(distance<300){
      lcd.print("Mid Clog Level");
      digitalWrite(YEL,HIGH);
      digitalWrite(BUZ,HIGH);
      digitalWrite(PUMP,HIGH);
      }
      else if(distance<400){
        lcd.print("About Clog Level");
        digitalWrite(BLU,HIGH);
        digitalWrite(BUZ,LOW);
        }
        else{
          lcd.print("Safe Drain Level");
          digitalWrite(GRE,HIGH);
          digitalWrite(BLU,LOW);
          digitalWrite(YEL,LOW);
          digitalWrite(RED,LOW);
          digitalWrite(BUZ,LOW);
          digitalWrite(PUMP,LOW);
          if(gas>50){
             digitalWrite(BLU,HIGH);
             delay(500);
             digitalWrite(BLU,LOW);
            }
           if(temp>40){
              digitalWrite(YEL,HIGH);
             delay(500);
             digitalWrite(YEL,LOW);
            }
            if(digitalRead(MQ)==HIGH){
              digitalWrite(YEL,HIGH);
              delay(500);
              digitalWrite(YEL,LOW);
            }
          }
  
  delay(2000);

  

  
}
