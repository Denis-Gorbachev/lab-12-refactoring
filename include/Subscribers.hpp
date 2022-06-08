// Copyright 2022 Denis Gorbachev <denis.gorbachev2002@yandex.ru>
#ifndef INCLUDE_SUBSCRIBERS_HPP_
#define INCLUDE_SUBSCRIBERS_HPP_
#include <string>
#include <vector>

struct Item {
  std::string id;
  std::string name;
  float score = 0;
};

class Subscribers {
 public:
  Subscribers() = default;
  virtual ~Subscribers() = default;
  virtual void OnDataLoaded(const std::vector<Item>& old_items,
                  const std::vector<Item>& new_items) = 0;
  virtual void OnRawDataLoaded(const std::vector<std::string>& old_items,
                     const std::vector<std::string>& new_items) = 0;
  virtual void Skip(const Item& item) = 0;
};
#endif  // INCLUDE_SUBSCRIBERS_HPP_
