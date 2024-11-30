// COMP2811 Coursework 2 sample solution: main window

#include <QtWidgets>
#include <stdexcept>
#include <iostream>
#include "window.hpp"
#include "stats.hpp"
#include "model.hpp"
#include "homepage.hpp"
#include "samplespage.hpp"
#include "overviewpage.hpp"

static const int MIN_WINDOW_WIDTH = 950;
static const int MIN_WINDOW_HEIGHT = 350;
static const int MIN_TOOLBAR_WIDTH = 200;

MainWindow::MainWindow() : QMainWindow(), statsDialog(nullptr)
{
  createMainWidget();
  createFileSelectors();
  createButtons();
  createToolBar();
  createStatusBar();
  addFileMenu();
  addHelpMenu();

  setMinimumSize(MIN_WINDOW_WIDTH, MIN_WINDOW_HEIGHT);
  setWindowTitle("Water Pollutants App");
}

void MainWindow::createMainWidget()
{
  homePage = new HomePage();
  overviewPage = new OverviewPage();
  samplesPage = new SamplesPage(&model);

  pages = new QStackedWidget();

  pages->addWidget(homePage);
  pages->addWidget(overviewPage);
  pages->addWidget(samplesPage);

  setCentralWidget(pages);
}

void MainWindow::createFileSelectors()
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

void MainWindow::createButtons()
{
  homePageButton = new QPushButton("Home");
  samplesPageButton = new QPushButton("Samples Table");
  overviewPageButton = new QPushButton("Pollutants Overview");

  connect(homePageButton, SIGNAL(clicked()), this, SLOT(showHomePage()));
  connect(samplesPageButton, SIGNAL(clicked()), this, SLOT(showSamplesPage()));
  connect(overviewPageButton, SIGNAL(clicked()), this, SLOT(showOverviewPage()));

  loadButton = new QPushButton("Load Data");

  connect(loadButton, SIGNAL(clicked()), this, SLOT(openCSV()));
}

void MainWindow::createToolBar()
{
  QToolBar *toolBar = new QToolBar();

  QLabel *titleLabel = new QLabel("<h2>Water Pollutants<br/>App</h2>");
  titleLabel->setAlignment(Qt::AlignHCenter);

  toolBar->setMinimumWidth(MIN_TOOLBAR_WIDTH);

  // Create the navigation button group
  QGroupBox *navButtonGroup = new QGroupBox();
  QVBoxLayout *navButtonLayout = new QVBoxLayout();
  QLabel *navLabel = new QLabel("<b>Navigation</b>");

  navButtonLayout->addWidget(navLabel);
  navButtonLayout->addWidget(homePageButton);
  navButtonLayout->addWidget(overviewPageButton);
  navButtonLayout->addWidget(samplesPageButton);
  navButtonGroup->setLayout(navButtonLayout);

  // Create the load document group
  QGroupBox *loadFileGroup = new QGroupBox();
  QVBoxLayout *loadFileLayout = new QVBoxLayout();
  QLabel *loadFileLabel = new QLabel("<b>File Settings</b>");

  loadFileLayout->addWidget(loadFileLabel);
  loadFileLayout->addWidget(loadButton);
  loadFileLayout->addStretch();
  loadFileGroup->setLayout(loadFileLayout);

  // Add the components to the toolbar
  toolBar->addWidget(titleLabel);
  toolBar->addSeparator();
  toolBar->addWidget(navButtonGroup);
  toolBar->addWidget(loadFileGroup);

  addToolBar(Qt::LeftToolBarArea, toolBar);
}

void MainWindow::createStatusBar()
{
  fileInfo = new QLabel("Current file: <none>");
  QStatusBar *status = statusBar();
  status->addWidget(fileInfo);
}

void MainWindow::addFileMenu()
{
  QAction *locAction = new QAction("Set Data &Location", this);
  locAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_L));
  connect(locAction, SIGNAL(triggered()), this, SLOT(setDataLocation()));

  QAction *closeAction = new QAction("Quit", this);
  closeAction->setShortcut(QKeySequence::Close);
  connect(closeAction, SIGNAL(triggered()), this, SLOT(close()));

  QMenu *fileMenu = menuBar()->addMenu("&File");
  fileMenu->addAction(locAction);
  fileMenu->addAction(closeAction);
}

void MainWindow::addHelpMenu()
{
  QAction *aboutAction = new QAction("&About", this);
  connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

  QAction *aboutQtAction = new QAction("About &Qt", this);
  connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

  QMenu *helpMenu = menuBar()->addMenu("&Help");
  helpMenu->addAction(aboutAction);
  helpMenu->addAction(aboutQtAction);
}

void MainWindow::setDataLocation()
{
  QString directory = QFileDialog::getExistingDirectory(
      this, "Data Location", ".",
      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

  if (directory.length() > 0)
  {
    dataLocation = directory;
  }
}

void MainWindow::openCSV()
{
  if (dataLocation == "")
  {
    QMessageBox::critical(this, "Data Location Error",
                          "Data location has not been set!\n\n"
                          "You can specify this via the File menu.");
    return;
  }

  // auto filename = QString("%1_%2.csv")
  // .arg(significance->currentText()).arg(period->currentText());

  auto filename = QString("Y-2024.csv");
  auto path = dataLocation + "/" + filename;

  try
  {
    model.updateFromFile(path);
  }
  catch (const std::exception &error)
  {
    QMessageBox::critical(this, "CSV File Error", error.what());
    return;
  }

  fileInfo->setText(QString("Current file: <kbd>%1</kbd>").arg(filename));
  samplesPage->updateColumnWidths();
  // table->resizeColumnsToContents();
}

void MainWindow::displayStats()
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

void MainWindow::about()
{
  QMessageBox::about(this, "About Quake Tool",
                     "Quake Tool displays and analyzes earthquake data loaded from"
                     "a CSV file produced by the USGS Earthquake Hazards Program.\n\n"
                     "(c) 2024 Nick Efford");
}

void MainWindow::showHomePage()
{
  pages->setCurrentIndex(0);
}

void MainWindow::showOverviewPage()
{
  pages->setCurrentIndex(1);
}

void MainWindow::showSamplesPage()
{
  pages->setCurrentIndex(2);
}