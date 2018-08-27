# Arduino Ticker Library

Based on the **Arduino Timer Object** library from Aron Bordin https://github.com/aron-bordin/ArduinoTimerObject

The **Arduino Ticker Library** allows you easily to create Ticker callbacks. In a predetermined interval, you can call a function. Works like a "thread", where a secondary function will run when necessary. The library use no interupts of the hardware timers and works with the **millis()** function.


## Installation

1. "Download":https://github.com/sstaub/Ticker/archive/master.zip the Master branch from GitHub.
2. Unzip and modify the folder name to "Ticker"
3. Move the modified folder on your Library folder (On your `Libraries` folder inside Sketchbooks or Arduino software).


## How to use

First, include the TimerObject to your project:

```
#include "Ticker.h"
```

Now, you can create a new object in setup():

```
Ticker tickerObject; 
tickerObject.setInterval(1000);
tickerObject.setCallback(callbackFunction);
tickerObject.start(); //start the ticker.
```

In your loop(), add:

```
tickerObject.update(); //it will check the Ticker 
and if necessary, it will run the callback function.
```


## IMPORTANT
If you use delay(), the Ticker will be ignored! You cannot use delay() command with the TimerObject. Instead of using delay, you can use the Ticker itself. For example, if you need that your loop run twice per second, just create a Ticker with 500 ms. It will have the same result that delay(500), but your code will be always state.

## Example

Complete example. Here we created three timers, you can run it and test the result in the Serial monitor and the on board LED.

```
#include "Ticker.h"

void printMessage();
void printCounter();
void blink();

int counter;
bool ledState;

Ticker timer1(printMessage, 0, SINGLE);
Ticker timer2(printCounter, 1000);
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
  digitalWrite(LED_BUILTIN, ledState);
  ledState = !ledState;
  }


```

## Documentation

### Modes
**SINGLE / REPEAT**

### States
**STOPPED / RUNNING / PAUSED**

### Constructors / Destructor
**Ticker()<br>
Ticker(fptr callback, unsigned long ms, bool mode = REPEAT)<br>
~Ticker()**
	
### Functions

**void setInterval(unsigned long ms)**<br>
Set callback interval.

**void setMode(int mode)**<br>
If mode is SINGLE, the callback will be called once, until you call start() or resume() again.

**void setCallback(ftpr callback);**<br>
Set function callback.

**void start()**<br>
Start the Ticker. Will count the interval from the moment that you start it. If it is paused, it will restart the Ticker.

**void resume()**<br>
Resume the Ticker. If not started, it will start it. If paused, it will resume it. For example, in a Ticker of 5 seconds, if it was paused in 3 seconds, the resume in continue in 3 seconds. Start will set passed time to 0 and restart until get 5 seconds.

**void pause()**<br>
Pause the Ticker, so you can resume it.

**void stop()**<br>
Stop the Ticker.

**void update()**<br>
Must to be called in the loop(), it will check the Ticker, and if necessary, will run the callback

**int state()**<br>
Returns the state of the Ticker.

**unsigned long time()**<br>
Returns the time passed since the last tick.

**unsigned long getInterval()**<br>
Get the interval of the Ticker.

**int getMode()**<br>
Get the mode of the Ticker.

**fptr getCallback()**<br>
Get the callback of the Ticker.

