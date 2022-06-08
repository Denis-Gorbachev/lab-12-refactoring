#include <algorithm>
#include <iostream>
#include <StatSender.hpp>
#include <Log.hpp>

constexpr size_t kMinLines = 10;

void StatSender::OnDataLoaded(const std::vector<Item>&,
                            const std::vector<Item>& new_items) {
  Log::getInstance().WriteDebug("StatSender::OnDataLoad");

  AsyncSend(new_items, "/items/loaded");
}

void StatSender::Skip(const Item& item) { AsyncSend({item},
                                                    "/items/skiped"); }

void StatSender::AsyncSend(
    const std::vector<Item>& items,
    std::string_view path) {
  Log::getInstance().Write(path);
  Log::getInstance().Write("send stat " + std::to_string(items.size()));

  for (const auto& item : items) {
    Log::getInstance().WriteDebug("send: " + item.id);
    // ... some code
    fstr << item.id << item.name << item.score;
    fstr.flush();
  }
}
