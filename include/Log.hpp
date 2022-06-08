#ifndef INCLUDE_LOG_HPP
#define INCLUDE_LOG_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <string_view>

class Log {
 public:
  Log();
  Log(const Log&) = delete;
  Log(const Log&&) = delete;
  Log operator=(const Log&) = delete;
  Log operator=(const Log&&) = delete;
  static Log& getInstance();
  void Write(std::string_view message) const;
  void WriteDebug(std::string_view message) const;

 private:
  size_t level_ = 0;
  mutable std::ostream* out_;
};
#endif  // INCLUDE_LOG_HPP
