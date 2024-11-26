// COMP2811 Coursework 1 sample solution: Quake class

#include <stdexcept>
#include <sstream>
#include "sample.hpp"

using namespace std;


Sample::Sample(const string& tm, const string& lbl, const string& def, const string& qual, double res, const string& un, int north, int east):
  time(tm), label(lbl), definition(def), qualifier(qual), result(res), unit(un), northing(north), easting(east)
{
  ostringstream error;

  if (result < 0.0) {
    error << "Invalid result: " << result;
    throw out_of_range(error.str());
  }

  if (northing < 0.0) {
    error << "Invalid northing: " << northing;
    throw out_of_range(error.str());
  }

  if (easting < 0.0) {
    error << "Invalid easting: " << easting;
    throw out_of_range(error.str());
  }
}


ostream& operator<<(ostream& out, const Sample& sample)
{
  return out << "Time: " << sample.getTime()
             << "\nLabel: " << sample.getLabel()
             << "\nDefinition: " << sample.getDefinition()
             << "\nQualifier: " << sample.getQualifier()
             << "\nResult: " << sample.getResult()
             << "\nUnit: " << sample.getUnit()
             << "\nNorthing: " << sample.getNorthing()
             << "\nEasting: " << sample.getEasting() << endl;
}
