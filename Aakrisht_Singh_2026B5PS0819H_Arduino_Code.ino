#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x20,16,2);

const int buttonPin = 8;  //setting up all the pins

const int trigPin = 4;
const int echoPin = 3;

const int ledPin = 9;

const int buzzPin = 13;

float distance;		//setting up all the variables
long duration;
int lightvalue;
int buttonState;

unsigned long dangerTime = 0;
unsigned long ledTime;
unsigned long Timer;

enum State {	//defining a datatype that can hold 5 different values
  OPEN_SEA,
  ANCHOR_DROPPED,
  WRECKED,
  STORM,
  CHARYBDIS
};

State state = OPEN_SEA;  //defining a variable of type state and setting it to open sea

void setup() {
  
  Serial.begin(9600);  //serial and lcd setup
  Serial.println(state);
  
  lcd.init();
  lcd.clear();         
  lcd.backlight();
  
  pinMode(trigPin, OUTPUT);  //setting up all the pins
  pinMode(echoPin, INPUT);
  
  pinMode(ledPin, OUTPUT);
  
  pinMode(buzzPin, OUTPUT);
  
  pinMode(buttonPin, INPUT);
  
  lcd.setCursor(0, 0);		//printing open sea on lcd since it's the default
  lcd.clear();
  lcd.print("OPEN SEA");
  
  
  
 
}

void loop() {
	
  Timer = millis() - dangerTime;		//This is only for my own reference
  
  Serial.println(lightvalue);
  
  lightvalue = analogRead(A0);		
  
  buttonState = digitalRead(buttonPin);
  
  digitalWrite(trigPin, LOW); //reading the distance with the ultrasonic sensor
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;
  
  switch(state){		//the switch state function which checks which state currently the variable state is in, the executes the corressponding code that is assigned to that state
    case OPEN_SEA:		
    	if (buttonState==HIGH) {	//checks for anchor
          state=ANCHOR_DROPPED;
          lcd.setCursor(0, 0);
		  lcd.clear();
    	  lcd.print("ANCHOR_DROPPED");
         	}
        else if (lightvalue<512){	//checks for light
          state=STORM;
          dangerTime = millis();
          lcd.setCursor(0, 0);
		  lcd.clear();
    	  lcd.print("STORM");
        	}
    	else if (distance<100){	//check for distance
          state=CHARYBDIS;
          digitalWrite(buzzPin,HIGH);
          dangerTime = millis();
          lcd.setCursor(0, 0);
		  lcd.clear();
    	  lcd.print("CHARYBDIS");
        	}
    	break;
    case STORM:
    	
    	if (lightvalue>=512 && distance>=100){	//checks for open sea
          state=OPEN_SEA;
          digitalWrite(ledPin,LOW);
          lcd.setCursor(0, 0);
		  lcd.clear();
    	  lcd.print("OPEN_SEA");
          break;
        	}
    	else if (lightvalue>=512 && distance<100){ //checks for a direct transition to charybdis so that it retains the timer
          state=CHARYBDIS;
          digitalWrite(ledPin,LOW);
          digitalWrite(buzzPin,HIGH);
          lcd.setCursor(0, 0);
		  lcd.clear();
    	  lcd.print("CHARYBDIS");
          break;
        	}
    	
    	if (buttonState==HIGH) { //checks for anchor
          state=ANCHOR_DROPPED;
          digitalWrite(ledPin,LOW);
          lcd.setCursor(0, 0);
		  lcd.clear();
    	  lcd.print("ANCHOR_DROPPED");
          break;
    
         	}
    
    	if (millis() - ledTime >= 500){ //code for blinking led
          ledTime = millis();
        	if (digitalRead(ledPin)==HIGH){
          		digitalWrite(ledPin, LOW);
          		}
        	else{
            	digitalWrite(ledPin, HIGH);
          		}
        	}
    	if (Timer >= 5000){ //checking for wrecked
          state=WRECKED;
          digitalWrite(ledPin,LOW);
          lcd.setCursor(0, 0);
		  lcd.clear();
    	  lcd.print("WRECKED");
          break;
        	}
    	break;
    
    case CHARYBDIS:
    	
    	if (distance>=100 && lightvalue>=512){ //checking for open sea
          state=OPEN_SEA;
          digitalWrite(buzzPin,LOW);
          lcd.setCursor(0, 0);
		  lcd.clear();
    	  lcd.print("OPEN_SEA");
          break;
        	}
    	else if (distance>=100 && lightvalue<512){ //checking for direct transition to storm
          state=STORM;
          digitalWrite(buzzPin,LOW);
          lcd.setCursor(0, 0);
		  lcd.clear();
    	  lcd.print("STORM");
          break;
        	}
    	
    	if (buttonState==HIGH) { //check for anchor
          state=ANCHOR_DROPPED;
          digitalWrite(buzzPin,LOW);
          lcd.setCursor(0, 0);
		  lcd.clear();
    	  lcd.print("ANCHOR_DROPPED");
          break;
    
         	}
    
    	if (Timer>= 5000){ //check for wrecked
          state=WRECKED;
          digitalWrite(buzzPin,LOW);
          lcd.setCursor(0, 0);
		  lcd.clear();
    	  lcd.print("WRECKED");
          break;
        	}
    	break;
    
    case WRECKED: //wrecked is permanent
    	break;
    
    case ANCHOR_DROPPED: //check for open sea

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
