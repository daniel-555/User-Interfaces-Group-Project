// COMP2811 Coursework 1 sample solution: QuakeDataset class

#include <stdexcept>
#include "dataset.hpp"
#include "csv.hpp"

using namespace std;


void SampleDataset::loadData(const string& filename)
{
  csv::CSVReader reader(filename);

  data.clear();

  for (const auto& row: reader) {
    Sample sample{
      row["time"].get<>(),
      row["label"].get<>(),
      row["definition"].get<>(),
      row["qualifier"].get<>(),
      row["result"].get<double>(),
      row["unit"].get<>(),
      row["northing"].get<int>(),
      row["easting"].get<int>(),
    };
    data.push_back(sample);
  }
}

void SampleDataset::checkDataExists() const
{
  if (size() == 0) {
    throw std::runtime_error("Dataset is empty!");
  }
}
