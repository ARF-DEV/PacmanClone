#pragma once
#include<SDL.h>
class Timer {
public:
	Timer(float _delayTime)
		:
		delayTime(_delayTime) {}
	bool passing() {
		return timePass > delayTime;
	}
	void updateTicks() {
		prev = now;
		now = SDL_GetTicks64() / 1000.0f;
	}
	void updateTimePass() {
		timePass += (now - prev);
	}
	void resetTimePass() {
		timePass = 0;
		updateTicks();
	}
private:
	float delayTime;
	float prev = 0;
	float now = 0;
	float timePass = 0;
};