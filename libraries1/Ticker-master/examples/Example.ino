#include "Ticker.h"

void printMessage();
void printCounter();
void blink();

int counter;
bool state;

Ticker timer1(0, printMessage, SINGLE);
Ticker timer2(1000, printCounter);
Ticker timer3;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  timer3.setCallback(blink);
  timer3.setInterval(500);
  delay(2000);
  timer1.start();
  timer2.start();
  timer3.start();
  }

void loop() {
  timer1.update();
  timer2.update();
  timer3.update();
  }

void printCounter() {
  Serial.print("Counter ");
  Serial.println(counter);
  counter++;
  }

void printMessage() {
  Serial.println("Hello!");
  }

void blink() {
  digitalWrite(LED_BUILTIN, state);
  state = !state;
  }
