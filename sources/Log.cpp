#include <algorithm>
#include <iostream>
#include <Log.hpp>

void Log::Write(std::string_view message) const {
  *out_ << message << std::endl;
}

void Log::WriteDebug(std::string_view message) const {
  if (level_ > 0) *out_ << message << std::endl;
}

Log& Log::getInstance() {
  static Log log;
  return log;
}

Log::Log(): level_(0), out_(&std::cout) {}
