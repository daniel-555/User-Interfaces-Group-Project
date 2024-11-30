// COMP2811 Coursework 2 sample solution: main window

#pragma once

#include <QMainWindow>
#include "model.hpp"

class QString;
class QComboBox;
class QLabel;
class QPushButton;
class StatsDialog;
class SamplesPage;

class QuakeWindow: public QMainWindow
{
  Q_OBJECT

  public:
    QuakeWindow();

  private:
    void createMainWidget();
    void createFileSelectors();
    void createButtons();
    void createToolBar();
    void createStatusBar();
    void addFileMenu();
    void addHelpMenu();

    QString dataLocation;      // location of CSV data files
    QComboBox* significance;   // selector for quake feed significance level
    QComboBox* period;         // selector for quake feed time period
    QPushButton* loadButton;   // button to load a new CSV file
    QPushButton* statsButton;  // button to display dataset stats
    QLabel* fileInfo;          // status bar info on current file
    StatsDialog* statsDialog;  // dialog to display stats
    SamplesPage* samplesPage;

  private slots:
    void setDataLocation();
    void openCSV();
    void displayStats();
    void about();
};
