// C++ code
//
int mood = 0;
const int neutralMood = 0;
int buttonState = 0;
bool buttonPressed = false;
unsigned long touchedTimer = 0;
unsigned long reducedTimer = 0;
const long unTouchInterval = 5000;
const long reducedInterval = 5000;

const int buttonPin = 7;
const int RledPin = 8;
const int GledPin = 9;
const int BledPin = 10;
void setup()
{
  Serial.begin(9600);
  
  pinMode(buttonPin, INPUT);
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);
  
  mood = neutralMood;
  
}

void loop()
{
  showLEDState(mood);
  
  buttonState = digitalRead(buttonPin);
  
  if(buttonState == HIGH && !buttonPressed){
  	
    mood = mood + 1;
    if(mood > 20)mood = 20;
    touchedTimer = millis();
    buttonPressed = true;
  }
  if(buttonState == LOW && buttonPressed){
  	buttonPressed = false;
  }
  unsigned long currentTimer = millis();
  if(currentTimer - touchedTimer > unTouchInterval){
  	if(currentTimer - touchedTimer > reducedInterval){
      mood = mood -1;
      if(mood < 0) mood = 0;
      reducedTimer = currentTimer;
  }
  }
}

void showLEDState(int state){
  float brightnessInterval = 255 / 10.0;
  if(state >= neutralMood){
  	analogWrite(RledPin, 0);
    analogWrite(GledPin, 255 - brightnessInterval * (state - neutralMood));
    analogWrite(BledPin, brightnessInterval * (state - neutralMood));
  }
  else{
    analogWrite(RledPin, brightnessInterval * (neutralMood - state));
    analogWrite(GledPin, 255 - brightnessInterval * (neutralMood - state));
    analogWrite(BledPin, 0);
  }
}