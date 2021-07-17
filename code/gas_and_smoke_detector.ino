// Credit: Gidey Gebrehiwot, Academia.com, Arduino.cc


#include<Servo.h>
Servo myservo;
int pos = 0;
int val;
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 10);
byte tx = 1;

const int Buzzer = 6;
const int DC_Motor = 7;

int gasC_1 = 0; //set initial tempC 0 for all MQ 3
int smkC_1 = 0; //set initial tempC 0 for all MQ 2

const int SensorPin1 = A0; //fire input sensor pin
const int SensorPin2 = A1;

String textForSMS;
void setup()
{
  lcd.begin(16, 2);
  delay(100);
  pinMode(tx, OUTPUT);
  myservo.attach(13);
  pinMode(Buzzer, OUTPUT);
  pinMode(SensorPin1, INPUT);
  pinMode(SensorPin2, INPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(DC_Motor, OUTPUT);

  mySerial.begin(9600);
  Serial.begin(9600); //Start the serial connection with the computer
}
void loop()
{
  int gasC_1 = analogRead(SensorPin1);
  int SmkC_1 = analogRead(SensorPin2);
  gasC_1 = analogRead(SensorPin1); //read the value from the LM35 sensor
  gasC_1 = (5.0 * gasC_1 * 100.0) / 1024.0; //convert the analog data to temperature
  smkC_1 = analogRead(SensorPin2); //read the value from the MQ 2 sensor
  smkC_1 = (5.0 * smkC_1 * 100.0) / 1024.0; //convert the analog data to temperature
  delay(50);



  if (gasC_1 >= 100 || smkC_1 >= 100)
  {
    val = analogRead(pos);
    val = map(val, 0, 1023, 0, 180);
    myservo.write(val);
    delay(50);
    digitalWrite(DC_Motor, HIGH);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  THERE IS FIRE ");
    lcd.setCursor(0, 1);
    lcd.print(" NOT SAFE HERE ");
    delay(100);
    lcd.clear();
    lcd.print("Sending SMS...");
    delay(100);

    digitalWrite(Buzzer, HIGH);
    delay(200);
    digitalWrite(Buzzer, LOW);
    delay(200);
    digitalWrite(Buzzer, HIGH);
    delay(200);
    digitalWrite(Buzzer, LOW);
    delay(5);


    Serial.print("AT+CMGF=1\r");
    delay(100);
    Serial.print("AT+CMGS=\"+233266302607\"\r");
    Serial.print("FIRE ALERT! Please Be Informed that Fire has Occured!\r");


    delay(200);
    Serial.println((char)26); // End AT command with a ^Z, ASCII code 26
    delay(200);
    Serial.println();
  }
  else
  {
    digitalWrite(DC_Motor, LOW);
    myservo.write(95);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("    NO FIRE    ");
    lcd.setCursor(0, 1);
    lcd.print("   ALL SAFE   ");
  }
}

// Credit: Gidey Gebrehiwot, Academia.com, Arduino.cc
