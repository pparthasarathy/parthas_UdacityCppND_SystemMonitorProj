#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath); //"/etc/os-release"
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename); //"/proc"+"/version"
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// Done TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  u_int8_t count = 0;
  string line;
  string key;
  long value[2]={0,0};
  long MemTotal = 0;
  long MemFree = 0;
  long MemUsed = 0;
  float MemUtilization = 0.0;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);//"/proc"+"/meminfo"
  if (stream.is_open()) {
    while (count < 2) { 
      std::getline(stream, line);
      std::istringstream linestream(line);
      linestream >> key >> value[count];
      ++count;
    }
  }
  MemTotal = value[0];
  MemFree = value[1];
  MemUsed = MemTotal - MemFree;
  MemUtilization = (float) MemUsed/ (float) MemTotal;
  return (float) MemUtilization;
}

// Done TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  string line = "";
  long up_time = 0;
  long idle_time = 0;
  std::ifstream stream(kProcDirectory + kUptimeFilename); //"/proc"+"/uptime"
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> up_time >> idle_time;
  }
  return up_time;
}

// Done TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  // /proc/stat gives:
  // cpu  user    nice system idle     iowait irq   softirq   steal   guest   guest_nice
  // cpu  1008620 1462 289235 50122643 22893  0     9784      0       0       0
  // Total CPU time since boot = user+nice+system+idle+iowait+irq+softirq+steal
  string line = "";
  string cpu = "";
  long user = 0;
  long nice = 0;
  long system = 0;
  long idle = 0;
  long iowait = 0;
  long irq = 0;
  long softirq = 0;
  long steal = 0;
  std::ifstream stream(kProcDirectory + kStatFilename); //"/proc"+"/uptime"
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;
  }
  return (user+nice+system+idle+iowait+irq+softirq+steal);
}

// Done TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
  // /proc/stat gives:
  // cpu  user    nice system idle     iowait irq   softirq   steal   guest   guest_nice
  // cpu  1008620 1462 289235 50122643 22893  0     9784      0       0       0
  // Total Active time since boot = user+nice+system+irq+softirq+steal
  string line = "";
  string cpu = "";
  long user = 0;
  long nice = 0;
  long system = 0;
  long idle = 0;
  long iowait = 0;
  long irq = 0;
  long softirq = 0;
  long steal = 0;
  std::ifstream stream(kProcDirectory + kStatFilename); //"/proc"+"/uptime"
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;
  }
  return (user+nice+system+irq+softirq+steal);
}

// Done TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { 
  // /proc/stat gives:
  // cpu  user    nice system idle     iowait irq   softirq   steal   guest   guest_nice
  // cpu  1008620 1462 289235 50122643 22893  0     9784      0       0       0
  // Total CPU time since boot = user+nice+system+idle+iowait+irq+softirq+steal
  string line = "";
  string cpu = "";
  long user = 0;
  long nice = 0;
  long system = 0;
  long idle = 0;
  long iowait = 0;
  std::ifstream stream(kProcDirectory + kStatFilename); //"/proc"+"/uptime"
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> cpu >> user >> nice >> system >> idle >> iowait;
  }
  return (idle+iowait);  
}

// Done TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string line = "";
  string key = "";
  int value = 0;
  std::ifstream stream(kProcDirectory + kStatFilename); //"/proc"+"/stat""}
  if (stream.is_open()) {
    while (std::getline(stream, line)) { 
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "processes") {
          break;
      }
    }
  }
  return value;
}

// Done TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string line = "";
  string key = "";
  int value = 0;
  std::ifstream stream(kProcDirectory + kStatFilename); //"/proc"+"/stat""}
  if (stream.is_open()) {
    while (std::getline(stream, line)) { 
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "procs_running") {
        break;
      }
    }
  }
  return value;
}

// Done TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  string line = "";
  std::ifstream stream(kProcDirectory + to_string(pid) + kCmdlineFilename); //"/proc/"+"pid"+"/cmdline"
  if (stream.is_open()) {
    std::getline(stream, line);
  }
  return line;
}

// Done TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
float LinuxParser::Ram(int pid) { 
  string line = "";
  string key = "";
  string value = "";
  float result = 0;
  const string keyname = "VmSize:";
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatusFilename); //"/proc/"+"pid"+"/status"
  while (std::getline(stream, line)) {
    if (line.compare(0, keyname.size(), keyname) == 0) 
    {
      std::istringstream linestream(line);
      linestream >> key >> value;
      break;
    }
  }
  if(value.empty())
  {
    result = (float) 0.0;
  }
  else
  {
    result = stof(value) * 0.001; //convert from KB to MB
  }  
  return result;   
}

// Done TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
int LinuxParser::Uid(int pid) { 
  string line = "";
  string key = "";
  int value = 0;
  const string keyname = "Uid:";
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatusFilename); //"/proc/"+"pid"+"/status"
  while (std::getline(stream, line)) {
    if (line.compare(0, keyname.size(), keyname) == 0) 
    {
      std::istringstream linestream(line);
      linestream >> key >> value;
      break;
    }
  }
  return value; 
}

// Done TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int uid) { 
  string line = "";
  string result = "";
  std::ifstream stream(kPasswordPath); //"/etc/passwd"
  string key = ":x:" + to_string(uid) + ":";
  while (std::getline(stream, line)) {
    if (line.find(key) != std::string::npos) {
      result = line.substr(0, line.find(":"));
      break;
    }
  }
  return result; 
}

// Done TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  string line = "";
  long starttime = 0; //#22- Time when the process started in clock ticks
  long hertz = sysconf(_SC_CLK_TCK);
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename); //"/proc/"+"pid"+"/stat"
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    for (int n=1; n<23; n++)
    {
      long val;
      linestream >> val;
      if(n==22) starttime = val;
    }
  }
  return (long) (starttime / hertz);
}

// Done TODO: Read and return CPU utilization for specified process
float LinuxParser::CpuUtilization(int pid) { 
  long sysUptime = 0; 
  long utime = 0;//#14- CPU time spent in user code in clock ticks
  long stime = 0; //#15- CPU time spent in kernel code in clock ticks
  long cutime = 0; //#16- Waited-for children's CPU time spent in user code in clock ticks
  long cstime = 0; //#17- Waited-for children's CPU time spent in kernel code in clock ticks
  long starttime = 0; //#22- Time when the process started in clock ticks
  long val = 0;
  float total_time = 0.0;
  float seconds = 0.0;
  float cpuUtilization = 0.0;
  string line = "";
  long hertz = sysconf(_SC_CLK_TCK);
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename); //"/proc/"+"pid"+"/stat"
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    for (int n=1; n<23; n++)
    {
      val = 0;
      linestream >> val;
      if(n==14) utime = val;
      if(n==15) stime = val;
      if(n==16) cutime = val;
      if(n==17) cstime = val;
      if(n==22) starttime = val;
    }
  }
  total_time = (float) (utime+stime+cutime+cstime);
  sysUptime = LinuxParser::UpTime();
  seconds = (float) sysUptime - ((float)starttime / (float)hertz);
  cpuUtilization = (total_time / (float)hertz) / float(seconds);
  return cpuUtilization;
}