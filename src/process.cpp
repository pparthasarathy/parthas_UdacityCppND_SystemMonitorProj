#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include "linux_parser.h"

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// Done TODO: Return this process's ID
int Process::Pid() { return pid; }

// Constructor that initializes PID for process
Process::Process(int pid_value) { 
    pid = pid_value; 
    cpuUtilization = LinuxParser::CpuUtilization(pid);
}

// Done TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
    cpuUtilization = LinuxParser::CpuUtilization(pid); 
    ramUtilization = LinuxParser::Ram(pid);
    return cpuUtilization;
}

// Done TODO: Return the command that generated this process
string Process::Command() { 
    if(command.empty()) {
        command = LinuxParser::Command(pid);
    }
    return command;
}

// Done TODO: Return this process's memory utilization
string Process::Ram() { 
    ramUtilization = LinuxParser::Ram(pid);
    return to_string(ramUtilization); 
}

// Done TODO: Return the user (name) that generated this process
string Process::User() { 
    if(user.empty()) {
        user = LinuxParser::User(pid);
    }
    return user;    
}

// Done TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid); }

// Done TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
    return (this->ramUtilization < a.ramUtilization); 
}