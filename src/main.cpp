#include <Arduino.h>

#define LED1 PC13
//#define LED2 PB9
#define NUM_CIRCLES 6
#define CIRCLE_TO_TRACK 2

void fillCircleArray(int circleCoords[NUM_CIRCLES][2]);
void writeCircleToLED(int circleToRead);

void setup() {
  Serial.begin(9600);
  pinMode(LED1, OUTPUT);
  //pinMode(LED2, OUTPUT);
}

int gauntletCoords[NUM_CIRCLES][2];
int postCoords[2];
String readValue;
char readChar;

void loop() {
  fillCircleArray(gauntletCoords);
  
  writeCircleToLED(CIRCLE_TO_TRACK);
}

void fillCircleArray(int circleCoords[NUM_CIRCLES][2]) {
  while (Serial.available()) {
    readChar = Serial.read();
    if (readChar == 'G') {
      for (int i = 0; i < NUM_CIRCLES; i++) {
        readValue = Serial.readStringUntil(',');
        gauntletCoords[i][0] = readValue.toInt();
        readValue = Serial.readStringUntil(';');
        gauntletCoords[i][1] = readValue.toInt();
        // Serial.print(circleCoords[i][0]);
        // Serial.print(' ');
        // Serial.println(circleCoords[i][1]);
      }
    }
    else if (readChar == 'P') {
      readValue = Serial.readStringUntil(',');
      postCoords[0] = readValue.toInt();
      readValue = Serial.readStringUntil(';');
      postCoords[1] = readValue.toInt();
      // Serial.print(circleCoords[i][0]);
      // Serial.print(' ');
      // Serial.println(circleCoords[i][1]);
    }
  }
}

void writeCircleToLED(int circleToRead) {
  if (gauntletCoords[circleToRead][0] < 0) {
    digitalWrite(LED1, HIGH);
  }
  else {
    digitalWrite(LED1, LOW);
  }
  // if (circleCoords[circleToRead][1] < 0) {
  //   digitalWrite(LED2, HIGH);
  // }
  // else {
  //   digitalWrite(LED2, LOW);
  // }
}