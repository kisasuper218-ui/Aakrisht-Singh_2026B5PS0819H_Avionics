#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x20,16,2);

const int buttonPin = 8;

const int trigPin = 4;
const int echoPin = 3;

const int ledPin = 9;

const int buzzPin = 13;

float distance;
long duration;
int lightvalue;
int buttonState;

unsigned long dangerTime = 0;
unsigned long ledTime;
unsigned long Timer;

enum State {
  OPEN_SEA,
  ANCHOR_DROPPED,
  WRECKED,
  STORM,
  CHARYBDIS
};

State state = OPEN_SEA;

void setup() {
  
  Serial.begin(9600);
  Serial.println(state);
  
  lcd.init();
  lcd.clear();         
  lcd.backlight();
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  pinMode(ledPin, OUTPUT);
  
  pinMode(buzzPin, OUTPUT);
  
  pinMode(buttonPin, INPUT);
  
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print("OPEN SEA");
  
  
  
 
}

void loop() {
	
  Timer = millis() - dangerTime;
  
  Serial.println(lightvalue);
  
  lightvalue = analogRead(A0);
  
  buttonState = digitalRead(buttonPin);
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;
  
  switch(state){
    case OPEN_SEA:
    	if (buttonState==HIGH) {
          state=ANCHOR_DROPPED;
          lcd.setCursor(0, 0);
		  lcd.clear();
    	  lcd.print("ANCHOR_DROPPED");
         	}
        else if (lightvalue<512){
          state=STORM;
          dangerTime = millis();
          lcd.setCursor(0, 0);
		  lcd.clear();
    	  lcd.print("STORM");
        	}
    	else if (distance<100){
          state=CHARYBDIS;
          digitalWrite(buzzPin,HIGH);
          dangerTime = millis();
          lcd.setCursor(0, 0);
		  lcd.clear();
    	  lcd.print("CHARYBDIS");
        	}
    	break;
    case STORM:
    	
    	if (lightvalue>=512 && distance>=100){
          state=OPEN_SEA;
          digitalWrite(ledPin,LOW);
          lcd.setCursor(0, 0);
		  lcd.clear();
    	  lcd.print("OPEN_SEA");
          break;
        	}
    	else if (lightvalue>=512 && distance<100){
          state=CHARYBDIS;
          digitalWrite(ledPin,LOW);
          digitalWrite(buzzPin,HIGH);
          lcd.setCursor(0, 0);
		  lcd.clear();
    	  lcd.print("CHARYBDIS");
          break;
        	}
    	
    	if (buttonState==HIGH) {
          state=ANCHOR_DROPPED;
          digitalWrite(ledPin,LOW);
          lcd.setCursor(0, 0);
		  lcd.clear();
    	  lcd.print("ANCHOR_DROPPED");
          break;
    
         	}
    
    	if (millis() - ledTime >= 500){
          ledTime = millis();
        	if (digitalRead(ledPin)==HIGH){
          		digitalWrite(ledPin, LOW);
          		}
        	else{
            	digitalWrite(ledPin, HIGH);
          		}
        	}
    	if (Timer >= 5000){
          state=WRECKED;
          digitalWrite(ledPin,LOW);
          lcd.setCursor(0, 0);
		  lcd.clear();
    	  lcd.print("WRECKED");
          break;
        	}
    	break;
    
    case CHARYBDIS:
    	
    	if (distance>=100 && lightvalue>=512){
          state=OPEN_SEA;
          digitalWrite(buzzPin,LOW);
          lcd.setCursor(0, 0);
		  lcd.clear();
    	  lcd.print("OPEN_SEA");
          break;
        	}
    	else if (distance>=100 && lightvalue<512){
          state=STORM;
          digitalWrite(buzzPin,LOW);
          lcd.setCursor(0, 0);
		  lcd.clear();
    	  lcd.print("STORM");
          break;
        	}
    	
    	if (buttonState==HIGH) {
          state=ANCHOR_DROPPED;
          digitalWrite(buzzPin,LOW);
          lcd.setCursor(0, 0);
		  lcd.clear();
    	  lcd.print("ANCHOR_DROPPED");
          break;
    
         	}
    
    	if (Timer>= 5000){
          state=WRECKED;
          digitalWrite(buzzPin,LOW);
          lcd.setCursor(0, 0);
		  lcd.clear();
    	  lcd.print("WRECKED");
          break;
        	}
    	break;
    
    case WRECKED:
    	break;
    
    case ANCHOR_DROPPED:

    	if (buttonState == HIGH) {
        	state = OPEN_SEA;
          	lcd.setCursor(0, 0);
		  	lcd.clear();
    	  	lcd.print("OPEN_SEA");
        	break;
    	}

    	break;
  	}	
}