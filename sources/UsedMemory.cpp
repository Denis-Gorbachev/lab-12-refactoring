// Copyright 2022 Denis Gorbachev <denis.gorbachev2002@yandex.ru>
#include <algorithm>
#include <iostream>
#include <UsedMemory.hpp>

UsedMemory::UsedMemory() : used_(0) {}

void UsedMemory::OnDataLoaded(const std::vector<Item>& old_items,
                            const std::vector<Item>& new_items) {
  Log::getInstance().WriteDebug("UsedMemory::OnDataLoad");
  for (const auto& item : old_items) {
    used_ -= item.id.capacity();
    used_ -= item.name.capacity();
    used_ -= sizeof(item.score);
  }

  for (const auto& item : new_items) {
    used_ += item.id.capacity();
    used_ += item.name.capacity();
    used_ += sizeof(item.score);
  }
  Log::getInstance().Write("UsedMemory::OnDataLoad: new size = "
                           + std::to_string(used_));
}

void UsedMemory::OnRawDataLoaded(const std::vector<std::string>& old_items,
                               const std::vector<std::string>& new_items) {
  Log::getInstance().WriteDebug("UsedMemory::OnRawDataLoads");
  for (const auto& item : old_items) {
    used_ -= item.capacity();
  }

  for (const auto& item : new_items) {
    used_ += item.capacity();
  }
  Log::getInstance().Write("UsedMemory::OnDataLoad: new size = "
                           + std::to_string(used_));
}

size_t UsedMemory::used() const { return used_; }
