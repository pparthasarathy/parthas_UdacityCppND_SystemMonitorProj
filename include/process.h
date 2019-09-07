#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid_value);
  int Pid();                               // Done TODO: See src/process.cpp
  std::string User();                      // Done TODO: See src/process.cpp
  std::string Command();                   // Done TODO: See src/process.cpp
  float CpuUtilization();                  // Done TODO: See src/process.cpp
  std::string Ram();                       // Done TODO: See src/process.cpp
  long int UpTime();                       // Done TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // Done TODO: See src/process.cpp

  // Done TODO: Declare any necessary private members
 private:
    int pid;
    float cpuUtilization;
    float ramUtilization;
    std::string user;
    std::string command;
};

#endif