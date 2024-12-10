// adapted to a QWidget page from COMP2811
// Coursework 2 sample solution: main window

#pragma once

#include <QWidget>

class QTableView;
class SampleModel;

class SamplesPage : public QWidget
{
  Q_OBJECT
public:
  SamplesPage(SampleModel *);

public slots:
  void updateColumnWidths();

private:
  void createWidgets();
  void arrangeWidgets();

  SampleModel *model; // data model used by table
  QTableView *table;  // table of sample data
};
