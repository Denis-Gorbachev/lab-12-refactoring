
#include "PageContainer.hpp"

void Histogram::OnDataLoaded(const std::vector<Item> &,
                           const std::vector<Item> &new_items) {
  Log::getInstance().WriteDebug("Histogram::OnDataLoaded");
  _avg_score = 0;
  _discarded = 0;
  size_t i = 0;
  for (; i < new_items.size(); ++i) {
    _avg_score += new_items[i].score;
  }
  _avg_score /= static_cast<float>(i);
  Log::getInstance().WriteDebug("Current average score = "
                                + std::to_string(_avg_score));
}
void Histogram::Skip(const Item &) {
  Log::getInstance().WriteDebug("Histogram::Skip");
  _discarded++;
}
