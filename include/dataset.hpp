// Taken from COMP2811 Coursework 1 sample solution starter code

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

  std::vector<std::string> getDeterminands();
  std::vector<std::pair<std::string, int>> getCommonPollutants();
  std::vector<Sample *> getDeterminandSamples(const std::string &);

  Sample *oldest();
  Sample *newest();

private:
  std::vector<Sample> data;
  void checkDataExists() const;
};
