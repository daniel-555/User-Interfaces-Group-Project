// COMP2811 Coursework 1 sample solution: QuakeDataset class

#include <stdexcept>
#include "../include/dataset.hpp"
#include "../include/csv.hpp"

using namespace std;

void SampleDataset::loadData(const string &filename)
{
  csv::CSVReader reader(filename);

  data.clear();

  for (const auto &row : reader)
  {
    Sample sample{
        row["sample.sampleDateTime"].get<>(),
        row["determinand.label"].get<>(),
        row["determinand.definition"].get<>(),
        row["resultQualifier.notation"].get<>(),
        row["result"].get<double>(),
        row["determinand.unit.label"].get<>(),
        row["sample.samplingPoint.northing"].get<int>(),
        row["sample.samplingPoint.easting"].get<int>(),
    };
    data.push_back(sample);
  }
}

void SampleDataset::checkDataExists() const
{
  if (size() == 0)
  {
    throw std::runtime_error("Dataset is empty!");
  }
}
