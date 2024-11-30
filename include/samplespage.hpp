// COMP2811 Coursework 2 sample solution: main window

#pragma once

#include <QWidget>

class QTableView;
class SampleModel;

class SamplesPage : public QWidget
{

public:
  SamplesPage(SampleModel *);

  void updateColumnWidths();

private:
  void createWidgets();
  void arrangeWidgets();

  SampleModel *model; // data model used by table
  QTableView *table;  // table of quake data
};
