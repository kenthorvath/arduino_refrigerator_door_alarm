// Refrigerator Door Alert System
// By Kent Horvath <kenthorvath@gmail.com>
// Plays an alert when the refrigerator door has been open for more than 60 seconds

// [GND] 	-> 	[(+)5.1V zener diode(-)] 		-> [7]
// 							[5V_out(/)] 		-> [7]

// When the V_out switch is open, Pin[7] reads LOW, otherwise Pin[7] reads HIGH
// Thus, Pin[7] is HIGH, unless the door is open


#define delay_in_seconds 60


//Define some pins
int doorSwitchIn = 7; 
int piezoAlarmOut = 9; //using pulsing piezo from Radioshack (#2730066)

//Timer Count
int timeOpen = 0;


//Initialization
void setup() { 
  
  Serial.begin(9600); //For Debug
  
  pinMode(doorSwitchIn, INPUT);
  pinMode(piezoAlarmOut, OUTPUT);
}

//Main
void loop() { 
	if (doorIsOpen())
	{
		timeOpen += 1;
		delay(1000);

		if (timeOpen > delay_in_seconds)
		{
			while (doorIsOpen())
			{
				soundAlarm();
			}	
		}

		if (doorIsClosed())
		{
			disableAlarm();
			timeOpen = 0;
		}
	}
}

//Piezo Alarm
void soundAlarm(){

	digitalWrite(piezoAlarmOut, HIGH);
}

void disableAlarm(){
	digitalWrite(piezoAlarmOut, LOW);
}


//Door check logic
bool doorIsOpen() {
        if(!doorIsClosed()){
          Serial.println("doorIsOpen()");
        }
	return !doorIsClosed();
}

bool doorIsClosed() {
  
	return digitalRead(doorSwitchIn) == HIGH;
}