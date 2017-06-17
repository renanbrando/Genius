#define YELLOW_LED 2
#define WHITE_LED 3
#define GREEN_LED 4
#define BLUE_LED 5

#define UNDEFINED_LED -1

#define BUZZER 13

#define YELLOW_BUTTON 8
#define WHITE_BUTTON 9
#define GREEN_BUTTON 10
#define BLUE_BUTTON 11

#define ONE_SECOND 1000
#define HALF_SECOND 500

#define SEQUENCE_SIZE 4

enum States {
  NEXT_ROUND_GAME_READY,
  USER_ANSWERING,
  GAME_FINISHED_OK,
  GAME_FINISHED_ERROR
};

int lightSequence[SEQUENCE_SIZE];

int roundGame = 0;

int ledsAnswered = 0;

void setup() {
  Serial.begin(9600);
  
  startPorts();
  startGame();
}

void startPorts() {
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(WHITE_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  pinMode(YELLOW_BUTTON, INPUT_PULLUP);
  pinMode(WHITE_BUTTON, INPUT_PULLUP);
  pinMode(GREEN_BUTTON, INPUT_PULLUP);
  pinMode(BLUE_BUTTON, INPUT_PULLUP);

  pinMode(BUZZER, OUTPUT);
}

void startGame() {
  
  int game = analogRead(0);
  randomSeed(game);

  for (int i = 0; i < SEQUENCE_SIZE; i++) {
    lightSequence[i] = randomColour();
  }
}

int randomColour() {
  return random(YELLOW_LED, BLUE_LED + 1);
}

void loop() {
  switch (currentState()) {
    case NEXT_ROUND_GAME_READY:
      Serial.println("Get ready for the next round");
      prepareNewGame();
      break;
    case USER_ANSWERING:
      Serial.println("Your turn");
      readUserResponse();
      break;
    case GAME_FINISHED_OK:
      Serial.println("Game finished successfully");
      gameFinished();
      break;
    case GAME_FINISHED_ERROR:
      Serial.println("Game finished with an error");
      gameFinishedError();
      break;
  }
  delay(HALF_SECOND);

}

void prepareNewGame() {
  roundGame++;
  ledsAnswered = 0;
  if (roundGame <= SEQUENCE_SIZE) {
    switchRoundLeds();
  }
}

void readUserResponse() {
  int response = checaRespostaJogador();

  if (response == UNDEFINED_LED) {
    return;
  }
  
  if (response == lightSequence[ledsAnswered]) {
    ledsAnswered++; 
  } else {
    Serial.println("Wrong sequence");
    roundGame = SEQUENCE_SIZE + 2;
  }
}

int currentState() {
  if (roundGame <= SEQUENCE_SIZE) {
    if (ledsAnswered == roundGame) {
      return NEXT_ROUND_GAME_READY; 
    } else {
      return USER_ANSWERING;
    }
  } else if (roundGame == SEQUENCE_SIZE + 1) {
    return GAME_FINISHED_OK;
  } else {
    return GAME_FINISHED_ERROR;
  }
}

void switchRoundLeds() {
  for (int i = 0; i < roundGame; i++) {
    blinkLed(lightSequence[i]);
  }
}

int checaRespostaJogador() {
  if (digitalRead(YELLOW_BUTTON) == LOW) {
    return blinkLed(YELLOW_LED);
  }
  if (digitalRead(WHITE_BUTTON) == LOW) {
    return blinkLed(WHITE_LED);
  }
  if (digitalRead(GREEN_BUTTON) == LOW) {
    return blinkLed(GREEN_LED);
  }
  if (digitalRead(BLUE_BUTTON) == LOW) {
    return blinkLed(BLUE_LED);
  }

  return UNDEFINED_LED;
}

void gameFinished() {
  blinkLed(YELLOW_LED);
  blinkLed(WHITE_LED);
  blinkLed(GREEN_LED);
  blinkLed(BLUE_LED);
  delay(HALF_SECOND);
}

void gameFinishedError() {
  switchSound(300);
  digitalWrite(YELLOW_LED,HIGH);
  digitalWrite(WHITE_LED,HIGH);
  digitalWrite(GREEN_LED,HIGH);
  digitalWrite(BLUE_LED,HIGH);
  delay(ONE_SECOND);
  digitalWrite(YELLOW_LED,LOW);
  digitalWrite(WHITE_LED,LOW);
  digitalWrite(GREEN_LED,LOW);
  digitalWrite(BLUE_LED,LOW);
  delay(HALF_SECOND);
}

int blinkLed(int ledPort) {

  verifyLedSound(ledPort);

  digitalWrite(ledPort,HIGH);
  delay(ONE_SECOND);
  digitalWrite(ledPort,LOW);
  delay(HALF_SECOND);

  return ledPort;
}

void switchSound(int frequency) {
  tone(BUZZER,frequency, 100);
}

void verifyLedSound(int ledPort) {
  switch (ledPort) {
    case YELLOW_LED:
      switchSound(2000);
      break;
    case WHITE_LED:
      switchSound(2200);
      break;
    case GREEN_LED:
      switchSound(2400);
      break;
    case BLUE_LED:
      switchSound(2500);
      break;
  }
}

int calculatesLedTime() {
  int potentiometer = analogRead(1);
  Serial.println(potentiometer);
  return potentiometer;
}

