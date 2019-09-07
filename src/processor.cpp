#include "processor.h"
#include "linux_parser.h"
#include <unistd.h>

// Done TODO: Returns the current CPU utilization over deltatime seconds
float Processor::Utilization() { 
    float totald = 0;
    float idled = 0;
    long PrevTotal = Jiffies(); 
    long PrevIdle = IdleJiffies();
    sleep(deltatime);
    totalJiffies = Jiffies();
    idleJiffies = IdleJiffies();
    activeJiffies = ActiveJiffies();
    totald = (float) (totalJiffies - PrevTotal);
    idled = (float) (idleJiffies - PrevIdle);
    currentUtilization = (totald - idled)/totald;
    return currentUtilization;
}

// Done TODO: Returns the aggregate CPU utilization
float Processor::OverallUtilization() { 
    totalJiffies = Jiffies();
    idleJiffies = IdleJiffies();
    activeJiffies = ActiveJiffies();
    cpuUtilization = activeJiffies/totalJiffies;
    return cpuUtilization;
}

// Done TODO: Read and return the number of jiffies for the system
long Processor::Jiffies() { return LinuxParser::Jiffies(); }

// Done TODO: Read and return the number of active jiffies for the system
long Processor::ActiveJiffies() { return LinuxParser::ActiveJiffies(); }

// Done TODO: Read and return the number of idle jiffies for the system
long Processor::IdleJiffies() { return LinuxParser::IdleJiffies(); }