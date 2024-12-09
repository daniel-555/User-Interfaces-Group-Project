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
class POPPage;
class LitterPage;

class SampleModel;
class SampleDataset;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow();

signals:
  void datasetUpdated(SampleDataset *);

private:
  void createMainWidget();
  void createFileSelectors();
  void createButtons();
  void createToolBar();
  void createStatusBar();
  void addFileMenu();
  void addHelpMenu();
  void makeConnections();

  QString dataLocation; // location of CSV data files
  QLabel *fileInfo;     // status bar info on current file
  QPushButton *loadButton;
  QLabel *yearLabel;
  QComboBox *datasetYear;
  QLabel *regionLabel;
  QComboBox *datasetRegion;

  QStackedWidget *pages;
  HomePage *homePage;
  SamplesPage *samplesPage;
  OverviewPage *overviewPage;
  POPPage *popPage;
  LitterPage *litterPage;

  QPushButton *homePageButton;
  QPushButton *samplesPageButton;
  QPushButton *overviewPageButton;
  QPushButton *popPageButton;
  QPushButton *litterPageButton;

  SampleModel model;
  SampleDataset dataset;

private slots:
  void setDataLocation();
  void openCSV();
  void displayStats();
  void about();

  void showHomePage();
  void showSamplesPage();
  void showOverviewPage();
  void showPOPPage();
  void showLitterPage();
};
