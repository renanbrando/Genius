
// LEDS CONST
#define YELLOW_LED 2
#define WHITE_LED  3
#define GREEN_LED  4
#define BLUE_LED   5

// BUTTONS CONST
#define YELLOW_BUTTON 10
#define WHITE_BUTTON  11
#define GREEN_BUTTON  12
#define BLUE_BUTTON   13
 
// TIME CONST
#define ON 1000
#define OFF 500

#define SEQUENCE_SIZE 5

int lightsSequence[SEQUENCE_SIZE];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  initPorts();
  initGame();
}

void loop() {
  // put your main code here, to run repeatedly:
  blinkLed(YELLOW_LED);

}

void initGame(){
  for (int index = 0; index < SEQUENCE_SIZE; index++){
    lightsSequence[index] = random(YELLOW_LED, BLUE_LED + 1);
  }
}

void initPorts(){
  pinMode(YELLOW_LED,OUTPUT);
  pinMode(WHITE_LED,OUTPUT);
  pinMode(GREEN_LED,OUTPUT);
  pinMode(BLUE_LED,OUTPUT);
  pinMode(YELLOW_BUTTON, INPUT_PULLUP);
  pinMode(WHITE_BUTTON, INPUT_PULLUP);
  pinMode(GREEN_BUTTON, INPUT_PULLUP);
  pinMode(BLUE_BUTTON, INPUT_PULLUP);
}

void blinkLed(int LED){
  digitalWrite(LED, HIGH);
  delay(ON);
  digitalWrite(LED, LOW);
  delay(OFF);
}


void blinkLeds(){
  for(int index = 0; index < SEQUENCE_SIZE ; index++){
        blinkLed(lightsSequence[index]);
  }
}

void highAll(){
  for(int index = 0; index < SEQUENCE_SIZE ; index++){
        digitalWrite(lightsSequence[index], HIGH);
  }
}

void lowAll(){
  for(int index = 0; index < SEQUENCE_SIZE ; index++){
        digitalWrite(lightsSequence[index], LOW);
  }
}


