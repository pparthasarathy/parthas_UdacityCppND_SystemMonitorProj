#ifndef PROCESSOR_H
#define PROCESSOR_H

#define deltatime 200 // delta time in milliseconds over which to calculate current utilization

class Processor {
 public:
    float Utilization();  // Done TODO: Returns the current CPU utilization over deltatime milliseconds
    float OverallUtilization(); // Done TODO: Returns the aggregate CPU utilization
  // Done TODO: Declare any necessary private members
 private:
    long totalJiffies = 0;
    long idleJiffies = 0;
    long activeJiffies = 0;
    float cpuUtilization = 0.0;
    float currentUtilization = 0.0;
    long Jiffies();
    long ActiveJiffies();
    long IdleJiffies();
};

#endif