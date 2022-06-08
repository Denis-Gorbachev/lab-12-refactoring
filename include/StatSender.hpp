// Copyright 2022 Denis Gorbachev <denis.gorbachev2002@yandex.ru>
#ifndef INCLUDE_STATSENDER_HPP_
#define INCLUDE_STATSENDER_HPP_

#include <algorithm>
#include <iostream>
#include <set>
#include <sstream>
#include "Subscribers.hpp"
#include "Log.hpp"
#include <string>
#include <vector>

class StatSender: public Subscribers {
 public:
  StatSender() = default;
  ~StatSender() override = default;
  void OnDataLoaded(const std::vector<Item>&,
                       const std::vector<Item>& new_items) override;
  void OnRawDataLoaded(const std::vector<std::string>&,
                     const std::vector<std::string>&) override {};
  void Skip(const Item& item) override;

 private:
  virtual void AsyncSend(const std::vector<Item>& items,
                         std::string_view path);
  std::ofstream fstr{"network", std::ios::binary};
};
#endif  // INCLUDE_STATSENDER_HPP_
