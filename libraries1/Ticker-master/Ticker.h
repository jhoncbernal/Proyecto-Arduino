/* Ticker library code is placed under the MIT license
 * Copyright (c) 2017 Stefan Staub
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef TICKER_H
#define TICKER_H

#include "Arduino.h"

/** Ticker modes
  *
  * @param REPEAT default, repeats infinitely
  * @param SINGLE a singleshot ticker
  *
  */
enum modus_t{REPEAT, SINGLE};

/** Ticker status
  *
  * @param STOPPED default, ticker is stopped
  * @param RUNNIBG ticker is running
	* @param PAUSED ticker is paused
  *
  */
enum status_t{STOPPED, RUNNING, PAUSED};

typedef void (*fptr)();

class Ticker {

public:

	/** create a Ticker object with none parameter which can set later
	*
	*/
	Ticker();

	/** create a Ticker object
	*
	* @param callback the name of the function to call
	* @param ms interval length
	* @param mode default REPEAT, set the mode REPEAT or SINGLE
	*
	*/
	Ticker(fptr callback, unsigned long ms, int mode = REPEAT);

	/** destructor for the Ticker object
	*
	*/
	~Ticker();

	/** interval time setting
	*
	* @param ms sets the interval time
	*
	*/
	void setInterval(unsigned long ms);

	/** mode setting
	*
	* @param mode sets the mode REPEAT or SINGLE
	*
	*/
	void setMode(int mode);

	/** callback setting
	*
	* @param callback sets the name of the function to call
	*
	*/
	void setCallback(fptr callback);

	/** start the ticker
	*
	*/
	void start();

	/** resume the ticker. If not started, it will start it.
	*
	*/
	void resume();

	/** pause the ticker
	*
	*/
	void pause();

	/** stops the ticker
	*
	*/
	void stop();

	/** must to be called in the main loop(), it will check the Ticker, and if necessary, will run the callback
	*
	*/
	void update();

	/** get the sate of the ticker
	*
	* @returns the state of the ticker: STOPPED, RUNNING or PAUSED
	*/
	int state();

	/** actual ellapsed time
	*
	* @returns the ellapsed time after the last tick
	*
	*/
	unsigned long int time();

	/** get the interval time
	*
	* @returns the interval time of the ticker
	*
	*/
	unsigned long int getInterval();

	/** get the ticker mode
	*
	* @returns the mode of the ticker
	*
	*/
	int getMode();

	/** get the callback pointer
	*
	* @returns the function pointer of the callback
	*
	*/
	fptr getCallback();

private:
	void init(fptr callback, unsigned long ms, int mode);
	unsigned long interval;
	bool enabled;
	int modus;
	int status;
	fptr call;
	bool tick();
	unsigned long lastTime;
	unsigned long diffTime;//used when I pause the Ticker and need to resume
};

#endif // TIMER_H
