// Copyright 2022 Denis Gorbachev <denis.gorbachev2002@yandex.ru>
#ifndef INCLUDE_HISTOGRAM_HPP_
#define INCLUDE_HISTOGRAM_HPP_
#include "Subscribers.hpp"
#include "Log.hpp"
#include <string>
#include <vector>

class Histogram: public Subscribers {
 public:
  Histogram(): _avg_score(0), _discarded(0) {}
  ~Histogram() override = default;
  void OnDataLoaded(const std::vector<Item> &,
                  const std::vector<Item> &new_items) override;
  void OnRawDataLoaded(const std::vector<std::string> &,
                      const std::vector<std::string> &) override {};
  void Skip(const Item&) override;
  [[nodiscard]] float get_avg() const { return _avg_score; }
  [[nodiscard]] size_t get_discarded() const { return _discarded; }
 private:
  float _avg_score;
  size_t _discarded;
};
#endif  // INCLUDE_HISTOGRAM_HPP_
