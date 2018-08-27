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

#include "Ticker.h"

Ticker::Ticker() {
	init(NULL, 0, false);
	}

Ticker::Ticker(fptr callback, unsigned long ms, int mode) {
	init(callback, ms, mode);
	}

Ticker::~Ticker() {}

void Ticker::init(fptr callback, unsigned long ms, int mode) {
	setInterval(ms);
	setMode(mode);
	setCallback(callback);
	enabled = false;
	lastTime = 0;
	}

void Ticker::setInterval(unsigned long ms) {
	interval = (ms > 0) ? ms : 0;
	}

void Ticker::setMode(int mode) {
	modus = mode;
	}

void Ticker::setCallback(fptr callback) {
	call = callback;
	}

void Ticker::start() {
	if (getCallback() == NULL) return;
	lastTime = millis();
	enabled = true;
	status = RUNNING;
	}

void Ticker::resume() {
	if (getCallback() == NULL) return;
	lastTime = millis() - diffTime;
	enabled = true;
	}

void Ticker::stop() {
	enabled = false;
	status = STOPPED;
	}

void Ticker::pause() {
	diffTime = millis() - lastTime;
	enabled = false;
	status = PAUSED;
	}

void Ticker::update() {
	if(tick()) call();
	}

bool Ticker::tick() {
	if(!enabled)	return false;
	if(lastTime > millis()*2) lastTime = 0;
	if ((millis() - lastTime) >= interval) {
		lastTime = millis();
		if(modus == SINGLE) enabled = false;
	  return true;
		}
	return false;
	}

int Ticker::state() {
	return status;
	}

unsigned long Ticker::time() {
	return millis() - lastTime;
	}

unsigned long Ticker::getInterval() {
	return interval;
	}

int Ticker::getMode() {
	return modus;
	}

fptr Ticker::getCallback() {
	return call;
	}
