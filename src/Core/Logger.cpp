#include "Logger.hpp"

using namespace Core;

//#include <HardwareSerial.h>

#define DBG_OUTPUT_PORT Serial

void
Logger::initialize() {
  //DBG_OUTPUT_PORT.begin(115200);
  //DBG_OUTPUT_PORT.setDebugOutput(false);
  //DBG_OUTPUT_PORT.println("");
}

void
Logger::message(const std::string& message) {
  //DBG_OUTPUT_PORT.print("MESSAGE: ");
  //DBG_OUTPUT_PORT.println(message.c_str());
}

void
Logger::warning(const std::string& message) {
  //DBG_OUTPUT_PORT.print("WARNING: ");
  //DBG_OUTPUT_PORT.println(message.c_str());
}

void
Logger::error(const std::string& message) {
  //DBG_OUTPUT_PORT.print("ERROR: ");
  //DBG_OUTPUT_PORT.println(message.c_str());
}
