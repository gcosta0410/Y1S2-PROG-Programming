//T02_G10
#include <vector>
#include "./include/Timer.h"  

// Default Timer class constructor, starts the timer on criation
Timer::Timer(){
	this->start = std::chrono::steady_clock::now();
}
// Stops the timer
void Timer::stop(){
    this->end = std::chrono::steady_clock::now();
    this->time_elapsed = this->end - this->start; // Total time since start of the game
    this->elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(time_elapsed).count(); // Convert total time to milliseconds
}
// Returns the time till game end in hh::mm:ss.ms format
std::string Timer::getTime(){
    
    long long total_ms = this->elapsed_time;

    // No magic numbers here!
    const int MS_IN_AN_HOUR = 3600000;
    const int MS_IN_A_MIN = 60000;
    const int MS_IN_A_SEC = 1000;

    // Convert milliseconds to hours - 3 600 000 milliseconds in an hour
    long long total_hr = total_ms / MS_IN_AN_HOUR;
    total_ms = total_ms - MS_IN_AN_HOUR * total_hr;

    // 60 000 milliseconds in a minute
    long long total_min = total_ms / MS_IN_A_MIN;
    total_ms = total_ms - MS_IN_A_MIN * total_min;

    // 1 000 milliseconds in a second
    long long total_sec = total_ms / MS_IN_A_SEC;
    total_ms = total_ms - MS_IN_A_SEC * total_sec;

    std::string formated_time = "";
    std::vector<long long> time = {total_hr, total_min, total_sec, total_ms};

    // For element with index i in time std::vector, format time string to have 0s if number is <10
    for(int i = 0; i < time.size(); i++){

        // To solve a bug where sometimes the ms part of the timer would show up as "39" instead of "390"
        if(i == 3 && std::to_string(time[i]).length() < 3){
            if(time[i] < 10){
                formated_time += "0" + std::to_string(time[i]) + "0";
            }
            else{
                formated_time += std::to_string(time[i]) + "0";
            }
        }
        else{
            if(time[i] < 10){
                formated_time += "0" + std::to_string(time[i]);
            }
            else{
                formated_time += std::to_string(time[i]);
            }
            if(i == 0 || i == 1){
                formated_time += ":";
            }
            else if(i == 2){
                formated_time += ".";
            }
        }
    }
   return formated_time;
}


