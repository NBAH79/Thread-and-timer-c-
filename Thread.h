#pragma once
#include "stdafx.h"
/*
template<class T, void(T::*mem_fun)()>
inline void thread_to_member(void* p)
{
return (static_cast<T*>(p)->*mem_fun)();
}
*/

class Thread {
private:
	FLAG STOP;
	FLAG STOPED;
public:
	Thread() : STOP(false), STOPED(true) {};
	~Thread() { Stop(); };
	std::thread Start() {
		STOP = false;
		STOPED = false;
		return std::thread([this] { this->TheThread(); });
		}
	void Stop() {
		STOP = true;
	}
	void TheThread() {
		try {
			while (!STOP) { Function(); }
		} catch (...) {};
		STOP = false;
		STOPED = true;
	};
	virtual void Function(void) = 0;
};

class Timer : public Thread {
private:
	std::clock_t _delay;
	std::clock_t last;  
	std::clock_t now;
	void Function() {
		std::clock_t delta;
		do {
			std::this_thread::sleep_for(std::chrono::milliseconds(1)); //heavily relaxes the system 
			now = std::clock();
			delta = now - last;
		} while (delta < _delay);
		last = now;
		TFunction(delta);
	};	 //overrides
public:
	Timer() :Thread(), _delay(0) { last = std::clock(); };
	Timer(std::clock_t delay) :Thread(), _delay(delay) {};
	~Timer() {
		Stop();
	}

	void Delay(std::clock_t delay) { _delay = delay; };
	virtual void TFunction(std::clock_t) = 0;
};

