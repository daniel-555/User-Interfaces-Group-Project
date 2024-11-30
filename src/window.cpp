// COMP2811 Coursework 2 sample solution: main window

#include <QtWidgets>
#include <stdexcept>
#include <iostream>
#include "window.hpp"
#include "stats.hpp"
#include "homepage.hpp"
#include "samplespage.hpp"
#include "overviewpage.hpp"

static const int MIN_WIDTH = 950;


QuakeWindow::QuakeWindow(): QMainWindow(), statsDialog(nullptr)
{
  createMainWidget();
  createFileSelectors();
  createButtons();
  createToolBar();
  createStatusBar();
  addFileMenu();
  addHelpMenu();

  setMinimumWidth(MIN_WIDTH);
  setWindowTitle("Quake Tool");
}


void QuakeWindow::createMainWidget()
{
  samplesPage = new SamplesPage();
  homePage = new HomePage();
  overviewPage = new OverviewPage();

  setCentralWidget(overviewPage); 
}


void QuakeWindow::createFileSelectors()
{
  // QStringList significanceOptions;
  // significanceOptions << "significant" << "4.5" << "2.5" << "1.0" << "all";
  // significance = new QComboBox();
  // significance->addItems(significanceOptions);

  // QStringList periodOptions;
  // periodOptions << "hour" << "day" << "week" << "month";
  // period = new QComboBox();
  // period->addItems(periodOptions);
}


void QuakeWindow::createButtons()
{
  homePageButton = new QPushButton("Home");
  samplesPageButton = new QPushButton("Samples Table");
  overviewPageButton = new QPushButton("Pollutants Overview");
}


void QuakeWindow::createToolBar()
{
  QToolBar* toolBar = new QToolBar();

  // QLabel* significanceLabel = new QLabel("Significance");
  // significanceLabel->setAlignment(Qt::AlignVCenter);
  // toolBar->addWidget(significanceLabel);
  // toolBar->addWidget(significance);

  // QLabel* periodLabel = new QLabel("Period");
  // periodLabel->setAlignment(Qt::AlignVCenter);
  // toolBar->addWidget(periodLabel);
  // toolBar->addWidget(period);

  // toolBar->addSeparator();

  // toolBar->addWidget(loadButton);
  // toolBar->addWidget(statsButton);

  QLabel* titleLabel = new QLabel("<h2>Water Pollutants<br/>App</h2>");
  titleLabel->setAlignment(Qt::AlignHCenter);


  toolBar->setMinimumWidth(200);

  toolBar->addWidget(titleLabel);
  toolBar->addSeparator();
  toolBar->addWidget(homePageButton);
  toolBar->addWidget(overviewPageButton);
  toolBar->addWidget(samplesPageButton);
  

  addToolBar(Qt::LeftToolBarArea, toolBar);
}


void QuakeWindow::createStatusBar()
{
  fileInfo = new QLabel("Current file: <none>");
  QStatusBar* status = statusBar();
  status->addWidget(fileInfo);
}


void QuakeWindow::addFileMenu()
{
  QAction* locAction = new QAction("Set Data &Location", this);
  locAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_L));
  connect(locAction, SIGNAL(triggered()), this, SLOT(setDataLocation()));

  QAction* closeAction = new QAction("Quit", this);
  closeAction->setShortcut(QKeySequence::Close);
  connect(closeAction, SIGNAL(triggered()), this, SLOT(close()));

  QMenu* fileMenu = menuBar()->addMenu("&File");
  fileMenu->addAction(locAction);
  fileMenu->addAction(closeAction);
}


void QuakeWindow::addHelpMenu()
{
  QAction* aboutAction = new QAction("&About", this);
  connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

  QAction* aboutQtAction = new QAction("About &Qt", this);
  connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

  QMenu* helpMenu = menuBar()->addMenu("&Help");
  helpMenu->addAction(aboutAction);
  helpMenu->addAction(aboutQtAction);
}


void QuakeWindow::setDataLocation()
{
  QString directory = QFileDialog::getExistingDirectory(
    this, "Data Location", ".",
    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

  if (directory.length() > 0) {
    dataLocation = directory;
  }
}


void QuakeWindow::openCSV()
{
  // if (dataLocation == "") {
  //   QMessageBox::critical(this, "Data Location Error",
  //     "Data location has not been set!\n\n"
  //     "You can specify this via the File menu."
  //   );
  //   return;
  // }

  // auto filename = QString("%1_%2.csv")
  //   .arg(significance->currentText()).arg(period->currentText());

  // auto path = dataLocation + "/" + filename;

  // try {
  //   model.updateFromFile(path);
  // }
  // catch (const std::exception& error) {
  //   QMessageBox::critical(this, "CSV File Error", error.what());
  //   return;
  // }

  // fileInfo->setText(QString("Current file: <kbd>%1</kbd>").arg(filename));
  // table->resizeColumnsToContents();
}


void QuakeWindow::displayStats()
{
  // if (model.hasData()) {
  //   if (statsDialog == nullptr) {
  //     statsDialog = new StatsDialog(this);
  //   }

  //   statsDialog->show();
  //   statsDialog->raise();
  //   statsDialog->activateWindow();
  // }
}

void QuakeWindow::about()
{
  QMessageBox::about(this, "About Quake Tool",
    "Quake Tool displays and analyzes earthquake data loaded from"
    "a CSV file produced by the USGS Earthquake Hazards Program.\n\n"
    "(c) 2024 Nick Efford");
}

void QuakeWindow::showHomePage()
{

}

void QuakeWindow::showSamplesPage()
{

}

void QuakeWindow::showOverviewPage()
{
  
}