// COMP2811 Coursework 2 sample solution: main window

#include <QtWidgets>
#include <stdexcept>
#include <iostream>
#include "samplespage.hpp"

SamplesPage::SamplesPage()
{
  createWidgets();
  arrangeWidgets();

  setWindowTitle("Sample Table");
}

void SamplesPage::createWidgets()
{
  table = new QTableView();
  table->setModel(&model);

  QFont tableFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
  table->setFont(tableFont);
}

void SamplesPage::arrangeWidgets()
{
  QHBoxLayout *layout = new QHBoxLayout();
  layout->addWidget(table);

  setLayout(layout);
}