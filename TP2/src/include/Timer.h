//T02_G10
#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <string>

class Timer{
	public:
		Timer(); // Default Timer class constructor, starts the timer on criation
		void stop(); // Stops the timer
		std::string getTime(); // Returns the time till game end in hh::mm:ss.ms format

	private:
		std::chrono::steady_clock::time_point start;
		std::chrono::steady_clock::time_point end;
		std::chrono::steady_clock::duration time_elapsed;
		long long elapsed_time;

};
#endif //TIMER_H
