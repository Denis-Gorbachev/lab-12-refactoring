// Copyright 2022 Denis Gorbachev <denis.gorbachev2002@yandex.ru>
#ifndef INCLUDE_USEDMEMORY_HPP_
#define INCLUDE_USEDMEMORY_HPP_

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <string_view>
#include "Subscribers.hpp"
#include "Log.hpp"

class UsedMemory: public Subscribers {
 public:
  UsedMemory();
  ~UsedMemory() override = default;
  void OnDataLoaded(const std::vector<Item>& old_items,
                  const std::vector<Item>& new_items) override;
  void OnRawDataLoaded(const std::vector<std::string>& old_items,
                     const std::vector<std::string>& new_items) override;
  void Skip(const Item&) override {};
  size_t used() const;

 private:
  size_t used_ = 0;
};

#endif  // INCLUDE_USEDMEMORY_HPP_
