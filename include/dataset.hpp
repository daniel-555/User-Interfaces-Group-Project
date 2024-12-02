// COMP2811 Coursework 1 sample solution: QuakeDataset class

#pragma once

#include <vector>
#include "sample.hpp"

class SampleDataset
{
public:
  SampleDataset() {}
  SampleDataset(const std::string &filename) { loadData(filename); }
  void loadData(const std::string &);
  int size() const { return data.size(); }
  Sample operator[](int index) const { return data.at(index); }
  std::vector<std::pair<std::string, int>> getCommonPollutants();
  // Quake shallowest() const;
  // double meanDepth() const;
  // double meanMagnitude() const;

private:
  std::vector<Sample> data;
  void checkDataExists() const;
};
