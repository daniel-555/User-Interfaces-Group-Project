// COMP2811 Coursework 2 sample solution: main window

#pragma once

#include <QMainWindow>
#include "model.hpp"

class QString;
class QComboBox;
class QLabel;
class QPushButton;
class StatsDialog;
class QStackedWidget;

class SamplesPage;
class HomePage;
class OverviewPage;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow();

private:
  void createMainWidget();
  void createFileSelectors();
  void createButtons();
  void createToolBar();
  void createStatusBar();
  void addFileMenu();
  void addHelpMenu();

  QString dataLocation;     // location of CSV data files
  QLabel *fileInfo;         // status bar info on current file
  StatsDialog *statsDialog; // dialog to display stats

  QStackedWidget *pages;
  HomePage *homePage;
  SamplesPage *samplesPage;
  OverviewPage *overviewPage;

  QPushButton *homePageButton;
  QPushButton *samplesPageButton;
  QPushButton *overviewPageButton;

private slots:
  void setDataLocation();
  void openCSV();
  void displayStats();
  void about();

  void showHomePage();
  void showSamplesPage();
  void showOverviewPage();
};
