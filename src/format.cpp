#include <string>

#include "format.h"

using std::string;

// Done TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    std::string time_string;
    long hour = 0;
	long min = 0;
    long time = 0;
	long sec = 0;
    hour = seconds/3600;
    time = seconds%3600;
    min = time/60;
    sec = seconds%60;
    time_string = std::to_string(hour) + ":" + std::to_string(min) + ":" + std::to_string(sec);    
    return time_string; 
}