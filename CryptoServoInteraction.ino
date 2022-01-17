#include<Stepper.h>

const char* encryptMessage(String message);
const char* decryptMessage(String message);

const uint8_t hallSensorPin = A0;

char wordsToCipher[7][32] = {"Computation Museum\0", "Tim Berners Lee\0", "Apple\0", "Microsoft\0", "Steve Jobs\0", "Bill Gates\0", "Roman Cryptography\0"};
char selectedWord[32];
char currentlySelectedLetter;
int8_t SHIFT_FACTOR;

const uint16_t stepsPerRevolution = 2048;
Stepper myStepper = Stepper(stepsPerRevolution, 2, 4, 3, 5);

bool INTERACTION_SOLVED, INTERACTION_RUNNING;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A7));
  myStepper.setSpeed(6);
  pinMode(hallSensorPin, INPUT);
}

void loop() {
  if (!Serial) {
    Serial.begin(9600);
  }
  if (Serial.available()) {
    processSerialMessage();
  }
}

void gameLoop(char* message, char* TIMESTAMP) {
  const char* decryptedMessage = decryptMessage(message);
  uint8_t index = 0;
  myStepper.setSpeed(2);
  while (decryptedMessage[index] != '\0') {
    pointToLetter(toUpperCase(decryptedMessage[index++]));
  }
  Serial.print("COM:MSG_ACK;MSG:OPERATION COMPLETED SUCCESSFULLY");
  Serial.print(";ID:");
  Serial.print(TIMESTAMP);
  Serial.print("\r\n");
  Serial.flush();
}

void pointToLetter(char letterToPointTo) {
  Serial.println(letterToPointTo);
  switch (letterToPointTo) {
    case 'A':
      myStepper.step((currentlySelectedLetter - 'A') * 78);
      currentlySelectedLetter = 'A';
      break;
    case 'B':
      myStepper.step((currentlySelectedLetter - 'B') * 78);
      currentlySelectedLetter = 'B';
      break;
    case 'C':
      myStepper.step((currentlySelectedLetter - 'C') * 78);
      currentlySelectedLetter = 'C';
      break;
    case 'D':
      myStepper.step((currentlySelectedLetter - 'D') * 78);
      currentlySelectedLetter = 'D';
      break;
    case 'E':
      myStepper.step((currentlySelectedLetter - 'E') * 78);
      currentlySelectedLetter = 'E';
      break;
    case 'F':
      myStepper.step((currentlySelectedLetter - 'F') * 78);
      currentlySelectedLetter = 'F';
      break;
    case 'G':
      myStepper.step((currentlySelectedLetter - 'G') * 78);
      currentlySelectedLetter = 'G';
      break;
    case 'H':
      myStepper.step((currentlySelectedLetter - 'H') * 78);
      currentlySelectedLetter = 'H';
      break;
    case 'I':
      myStepper.step((currentlySelectedLetter - 'I') * 78);
      currentlySelectedLetter = 'I';
      break;
    case 'J':
      myStepper.step((currentlySelectedLetter - 'J') * 78);
      currentlySelectedLetter = 'J';
      break;
    case 'K':
      myStepper.step((currentlySelectedLetter - 'K') * 78);
      currentlySelectedLetter = 'K';
      break;
    case 'L':
      myStepper.step((currentlySelectedLetter - 'L') * 78);
      currentlySelectedLetter = 'L';
      break;
    case 'M':
      myStepper.step((currentlySelectedLetter - 'M') * 78);
      currentlySelectedLetter = 'M';
      break;
    case 'N':
      myStepper.step((currentlySelectedLetter - 'N') * 78);
      currentlySelectedLetter = 'N';
      break;
    case 'O':
      myStepper.step((currentlySelectedLetter - 'O') * 78);
      currentlySelectedLetter = 'O';
      break;
    case 'P':
      myStepper.step((currentlySelectedLetter - 'P') * 78);
      currentlySelectedLetter = 'P';
      break;
    case 'Q':
      myStepper.step((currentlySelectedLetter - 'Q') * 78);
      currentlySelectedLetter = 'Q';
      break;
    case 'R':
      myStepper.step((currentlySelectedLetter - 'R') * 78);
      currentlySelectedLetter = 'R';
      break;
    case 'S':
      myStepper.step((currentlySelectedLetter - 'S') * 78);
      currentlySelectedLetter = 'S';
      break;
    case 'T':
      myStepper.step((currentlySelectedLetter - 'T') * 78);
      currentlySelectedLetter = 'T';
      break;
    case 'U':
      myStepper.step((currentlySelectedLetter - 'U') * 78);
      currentlySelectedLetter = 'U';
      break;
    case 'V':
      myStepper.step((currentlySelectedLetter - 'V') * 78);
      currentlySelectedLetter = 'V';
      break;
    case 'W':
      myStepper.step((currentlySelectedLetter - 'W') * 78);
      currentlySelectedLetter = 'W';
      break;
    case 'X':
      myStepper.step((currentlySelectedLetter - 'X') * 78);
      currentlySelectedLetter = 'X';
      break;
    case 'Y':
      myStepper.step((currentlySelectedLetter - 'Y') * 78);
      currentlySelectedLetter = 'Y';
      break;
    case 'Z':
      myStepper.step((currentlySelectedLetter - 'Z') * 78);
      currentlySelectedLetter = 'Z';
      break;
  }
  delay(750);
}

void moveArrowToHomePosition() {
  myStepper.setSpeed(4);
  while (true) {
    long measure = 0;
    for (int i = 0; i < 10; i++) {
      int value =
        measure += analogRead(hallSensorPin);
    }
    measure /= 10;

    float outputV = measure * 5000.0 / 1023;
    //Serial.println(outputV);

    if (outputV < 1010) {
      currentlySelectedLetter = 'A';
      break;
    }

    myStepper.step(1);
  }
}

const char* encryptMessage(char* message) {
  return applyShift(message, SHIFT_FACTOR);
}

const char* decryptMessage(char* message) {
  return applyShift(message, 26 - SHIFT_FACTOR);
}

const char* applyShift(char* message, int8_t shiftFactor) {
  char* chars = message;
  uint8_t index = 0;
  while (chars[index] != '\0') {
    char c = chars[index];
    if (c >= 'A' && c <= 'Z')
      chars[index] = (char) ((c - 'A' + shiftFactor) % 26 + 'A');
    else if (c >= 'a' && c <= 'z')
      chars[index] = (char) ((c - 'a' + shiftFactor) % 26 + 'a');
    index++;
  }
  return chars;
}

void processSerialMessage() {
  const uint8_t BUFF_SIZE = 64; // make it big enough to hold your longest command
  static char buffer[BUFF_SIZE + 1]; // +1 allows space for the null terminator
  static uint8_t length = 0; // number of characters currently in the buffer

  char c = Serial.read();
  if ((c == '\r') || (c == '\n')) {
    // end-of-line received
    if (length > 0) {
      tokenizeReceivedMessage(buffer);
    }
    length = 0;
  } else {
    if (length < BUFF_SIZE) {
      buffer[length++] = c; // append the received character to the array
      buffer[length] = 0; // append the null terminator
    }
  }
}

void tokenizeReceivedMessage(char *msg) {
  const uint8_t COMMAND_PAIRS = 10;
  char* tokenizedString[COMMAND_PAIRS + 1];
  uint8_t index = 0;

  char* command = strtok(msg, ";");
  while (command != 0) {
    char* separator = strchr(command, ':');
    if (separator != 0) {
      *separator = 0;
      tokenizedString[index++] = command;
      ++separator;
      tokenizedString[index++] = separator;
    }
    command = strtok(0, ";");
  }
  tokenizedString[index] = 0;

  processReceivedMessage(tokenizedString);
}

void processReceivedMessage(char** command) {
  if (strcmp(command[1], "START") == 0) {
    startSequence(command[3]);
  } else if (strcmp(command[1], "PAUSE") == 0) {
    pauseSequence(command[3]);
  } else if (strcmp(command[1], "STOP") == 0) {
    stopSequence(command[3]);
  } else if (strcmp(command[1], "INTERACTION_SOLVED_ACK") == 0) {
    setInteractionSolved();
  } else if (strcmp(command[1], "PING") == 0) {
    ping(command[3]);
  } else if (strcmp(command[1], "BAUD") == 0) {
    setBaudRate(atoi(command[3]), command[5]);
  } else if (strcmp(command[1], "SETUP") == 0) {
    Serial.println("COM:SETUP;INT_NAME:Crypto Servo Interaction;BAUD:9600");
    Serial.flush();
  } else if (strcmp(command[1], "MSG") == 0) {
    gameLoop(command[3], command[5]);
  }
}

void startSequence(char* TIMESTAMP) {
  INTERACTION_SOLVED = false;
  INTERACTION_RUNNING = true;
  SHIFT_FACTOR = random(1, 26);

  for (uint8_t i = 0; i < sizeof(selectedWord); i++) {
    selectedWord[i] = 0;
  }
  strcpy(selectedWord, wordsToCipher[random(0, 7)]);

  Serial.print("COM:START_ACK;MSG:CT-");
  Serial.print(selectedWord);
  Serial.print(" SF-");
  Serial.print(SHIFT_FACTOR);
  Serial.print(" ET-");
  Serial.print(encryptMessage(selectedWord));
  Serial.print(";ID:");
  Serial.print(TIMESTAMP);
  Serial.print("\r\n");
  Serial.flush();

  moveArrowToHomePosition();
}

void pauseSequence(char* TIMESTAMP) {
  INTERACTION_RUNNING = !INTERACTION_RUNNING;
  if (INTERACTION_RUNNING) {
    Serial.print("COM:PAUSE_ACK;MSG:Device is now running;ID:");
  } else {
    Serial.print("COM:PAUSE_ACK;MSG:Device is now paused;ID:");
  }
  Serial.print(TIMESTAMP);
  Serial.print("\r\n");
  Serial.flush();
}

void stopSequence(char* TIMESTAMP) {
  INTERACTION_RUNNING = false;
  Serial.print("COM:STOP_ACK;MSG:Device is now stopped;ID:");
  Serial.print(TIMESTAMP);
  Serial.print("\r\n");
  Serial.flush();
}

void setInteractionSolved() {
  INTERACTION_SOLVED = true;
  INTERACTION_RUNNING = false;
}

void ping(char* TIMESTAMP) {
  Serial.print("COM:PING;MSG:PING;ID:");
  Serial.print(TIMESTAMP);
  Serial.print("\r\n");
  Serial.flush();
}

void setBaudRate(int baudRate, char* TIMESTAMP) {
  Serial.flush();
  Serial.begin(baudRate);
  Serial.print("COM:BAUD_ACK;MSG:The Baud Rate was set to ");
  Serial.print(baudRate);
  Serial.print(";ID:");
  Serial.print(TIMESTAMP);
  Serial.print("\r\n");
  Serial.flush();
}

//TODO: Change this method in order to validate if the interaction has been solved
bool checkWinning() {
  Serial.println("COM:INTERACTION_SOLVED;MSG:User Deciphered Message Correctly;PNT:2450");
  Serial.flush();
}
