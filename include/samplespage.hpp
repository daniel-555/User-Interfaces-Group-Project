// COMP2811 Coursework 2 sample solution: main window

#pragma once

#include <QWidget>
#include "model.hpp"

class QTableView;

class SamplesPage : public QWidget
{

public:
  SamplesPage();

private:
  void createWidgets();
  void arrangeWidgets();

  SampleModel model; // data model used by table
  QTableView *table; // table of quake data
};
