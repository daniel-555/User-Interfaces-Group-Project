// adapted from COMP2811 Coursework 1 sample solution: Quake class

#pragma once

#include <string>
#include <iostream>

class Sample
{
public:
  Sample(const std::string &, const std::string &, const std::string &, const std::string &, double, const std::string &, int, int);
  std::string getTime() const { return time; }
  std::string getLabel() const { return label; }
  std::string getDefinition() const { return definition; }
  std::string getQualifier() const { return qualifier; }
  double getResult() const { return result; }
  std::string getUnit() const { return unit; }
  int getEasting() const { return easting; }
  int getNorthing() const { return northing; }

private:
  std::string time;
  std::string label;
  std::string definition;
  std::string qualifier;
  double result;
  std::string unit;
  int northing;
  int easting;
};

std::ostream &operator<<(std::ostream &, const Sample &);
