#include <algorithm>
#include <iostream>
#include <set>
#include <PageContainer.hpp>

constexpr size_t kMinLines = 10;

PageContainer::PageContainer(StatSender* sender, UsedMemory* used_memory,
                             Histogram* hist) {
    push_sub(sender);
    push_sub(used_memory);
    push_sub(hist);
}

void PageContainer::push_sub(Subscribers* sub) {
  sub_.emplace_back(sub);
}

PageContainer::~PageContainer() {
  for (auto& sub : sub_) {
    delete sub;
  }
}

void PageContainer::Load(std::istream& io, float threshold) {
  LoadRawData(io);
  Reload(threshold);
}

const Item& PageContainer::ByIndex(size_t i) const { return data_[i]; }

const Item& PageContainer::ById(const std::string& id) const {
  auto it = std::find_if(std::begin(data_), std::end(data_),
                         [&id](const auto& i) { return id == i.id; });
  return *it;
}

void PageContainer::Reload(float threshold) {
  std::vector<Item> data;
  std::set<std::string> ids;
  for (const auto& line : raw_data_) {
    std::stringstream stream(line);

    Item item;
    stream >> item.id >> item.name >> item.score;

    if (auto&& [_, inserted] = ids.insert(item.id); !inserted) {
      throw std::runtime_error("already seen");
    }

    if (item.score > threshold) {
      data.push_back(std::move(item));
    } else {
      OnSkipped(item);
    }
  }

  if (data.size() < kMinLines) {
    throw std::runtime_error("oops");
  }

  OnDataLoaded(data);
  data_ = std::move(data);
}

void PageContainer::LoadRawData(std::istream& io) {

  std::vector<std::string> raw_data;

  if (!io) throw std::runtime_error("Can't open file.");

  while (!io.eof()) {
    std::string line;
    std::getline(io, line, '\n');
    raw_data.push_back(std::move(line));
  }

  if (raw_data.size() < kMinLines) {
    throw std::runtime_error("too small input stream");
  }
  OnRawDataLoaded(raw_data);
  raw_data_ = std::move(raw_data);
}

void PageContainer::OnDataLoaded(const std::vector<Item>& new_items) {
  for (auto& sub : sub_) {
    sub->OnDataLoaded(data_, new_items);
  }
}

void PageContainer::OnRawDataLoaded(const std::vector<std::string>& new_items) {
  for (auto& sub : sub_) {
    sub->OnRawDataLoaded(raw_data_, new_items);
  }
}

void PageContainer::OnSkipped(const Item& item) {
  for (auto& sub : sub_) {
    sub->Skip(item);
  }
}