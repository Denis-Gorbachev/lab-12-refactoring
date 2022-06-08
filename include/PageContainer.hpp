#ifndef INCLUDE_PAGECONTAINER_HPP
#define INCLUDE_PAGECONTAINER_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <string_view>
#include "Subscribers.hpp"
#include "Log.hpp"
#include "UsedMemory.hpp"
#include "StatSender.hpp"
#include "Histogram.hpp"

class PageContainer {
 public:
  explicit PageContainer(StatSender* sender = new StatSender,
                UsedMemory* used_memory = new UsedMemory,
                Histogram* hist = new Histogram);
  ~PageContainer();
  void push_sub(Subscribers* sub);
  void Load(std::istream& io, float threshold);
  [[nodiscard]] const Item& ByIndex(size_t i) const;
  [[nodiscard]] const Item& ById(const std::string& id) const;
  void Reload(float threshold);
  size_t get_size() {
    return (sub_.capacity()+
            data_.capacity() +
            raw_data_.capacity());
  }
 private:
  void LoadRawData(std::istream& io);
  void OnDataLoaded(const std::vector<Item>& new_items);
  void OnRawDataLoaded(const std::vector<std::string>& new_items);
  void OnSkipped(const Item& item);
  std::vector<Subscribers*> sub_;
  std::vector<Item> data_;
  std::vector<std::string> raw_data_;
};

#endif  // INCLUDE_PAGECONTAINER_HPP
