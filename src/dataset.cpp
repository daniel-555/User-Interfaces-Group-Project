// COMP2811 Coursework 1 sample solution: QuakeDataset class

#include <stdexcept>
#include <unordered_map>
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

vector<string> SampleDataset::getDeterminands()
{
  unordered_map<string, int> determinandMap;
  for (const auto &sample : data)
  {
    determinandMap[sample.getDefinition()]++;
  }

  vector<string> determinands;

  for (auto kv : determinandMap)
  {
    determinands.push_back(kv.first);
  }

  return determinands;
}

vector<pair<string, int>> SampleDataset::getCommonPollutants()
{
  unordered_map<string, int> frequencyMap;
  for (const auto &sample : data)
  {
    frequencyMap[sample.getDefinition()]++;
  }

  vector<pair<string, int>> frequencyVector(frequencyMap.begin(), frequencyMap.end());
  sort(frequencyVector.begin(), frequencyVector.end(), [](const auto &a, const auto &b)
       { return b.second < a.second; });

  vector<pair<string, int>> topDeterminands;
  for (int i = 0; i < 10 && i < frequencyVector.size(); ++i)
  {
    topDeterminands.push_back(frequencyVector[i]);
  }

  return topDeterminands;
}

vector<Sample *> SampleDataset::getDeterminandSamples(const string &determinand)
{
  vector<Sample *> samples;

  for (const auto &sample : data)
  {
    if (sample.getDefinition() == determinand)
    {
      samples.push_back(const_cast<Sample *>(&sample));
    }
  }

  return samples;
}

Sample *SampleDataset::newest()
{
  Sample *newest = &data[0];

  for (auto &sample : data)
  {
    if (sample.getTime() > newest->getTime())
    {
      newest = &sample;
    }
  }
  return newest;
}

Sample *SampleDataset::oldest()
{
  Sample *oldest = &data[0];

  for (auto &sample : data)
  {
    if (sample.getTime() < oldest->getTime())
    {
      oldest = &sample;
    }
  }
  return oldest;
}