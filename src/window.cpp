// adapted from COMP2811 Coursework 2 sample solution: main window

#include <QtWidgets>
#include <stdexcept>
#include <iostream>
#include "window.hpp"
#include "model.hpp"
#include "dataset.hpp"
#include "homepage.hpp"
#include "samplespage.hpp"
#include "overviewpage.hpp"
#include "POPpage.hpp"
#include "litterpage.hpp"

static const int MIN_WINDOW_WIDTH = 1000;
static const int MIN_WINDOW_HEIGHT = 700;
static const int MIN_TOOLBAR_WIDTH = 200;

MainWindow::MainWindow() : QMainWindow()
{
  createMainWidget();
  createFileSelectors();
  createButtons();
  createToolBar();
  createStatusBar();
  addFileMenu();
  addHelpMenu();
  makeConnections();

  setMinimumSize(MIN_WINDOW_WIDTH, MIN_WINDOW_HEIGHT);
  setWindowTitle(tr("Water Pollutants App"));
}

// Page creation
void MainWindow::createMainWidget()
{
  homePage = new HomePage();
  overviewPage = new OverviewPage();
  samplesPage = new SamplesPage(&model);
  popPage = new POPPage();
  litterPage = new LitterPage();

  pages = new QStackedWidget();

  pages->addWidget(homePage);
  pages->addWidget(overviewPage);
  pages->addWidget(samplesPage);
  pages->addWidget(popPage);
  pages->addWidget(litterPage);

  setCentralWidget(pages);
}

// Load options into datasetYear and datasetRegion combo boxes
void MainWindow::createFileSelectors()
{
  datasetYear = new QComboBox();
  for (int i = 2024; i >= 2000; i--)
  {
    datasetYear->addItem(QString::fromStdString(std::to_string(i)));
  }

  QStringList regionOptions;
  regionOptions
      << "Cambridgeshire and Bedfordshire"
      << "Cumbria and Lancashire"
      << "Derbyshire Nottinghamshire and Leicestershire"
      << "Devon and Cornwall"
      << "Essex Norfolk and Suffolk"
      << "Greater Manchester Merseyside and Cheshire"
      << "Hertfordshire and North London"
      << "Kent and South London"
      << "Lincolnshire and Northamptonshire"
      << "Northumberland Durham and Tees"
      << "Shropshire Herefordshire Worcestershire and Gloucestershire"
      << "Solent and South Downs"
      << "Staffordshire Warwickshire and West Midlands"
      << "Wessex"
      << "West Thames"
      << "Yorkshire";

  datasetRegion = new QComboBox();
  datasetRegion->addItems(regionOptions);
}

void MainWindow::createButtons()
{
  homePageButton = new QPushButton(tr("Home"));
  samplesPageButton = new QPushButton(tr("Samples Table"));
  overviewPageButton = new QPushButton(tr("Pollutants Overview"));
  popPageButton = new QPushButton(tr("Persistent Organic Pollutants"));
  litterPageButton = new QPushButton(tr("Environmental Litter Indicators"));

  loadButton = new QPushButton(tr("Load Data"));
}

void MainWindow::createToolBar()
{
  QToolBar *toolBar = new QToolBar();

  QLabel *titleLabel = new QLabel(tr("<h2>Water Pollutants<br/>App</h2>"));
  titleLabel->setAlignment(Qt::AlignHCenter);

  toolBar->setMinimumWidth(MIN_TOOLBAR_WIDTH);

  // Create the navigation button group
  QGroupBox *navButtonGroup = new QGroupBox();
  QVBoxLayout *navButtonLayout = new QVBoxLayout();
  QLabel *navLabel = new QLabel(tr("<b>Navigation</b>"));

  navButtonLayout->addWidget(navLabel);
  navButtonLayout->addWidget(homePageButton);
  navButtonLayout->addWidget(overviewPageButton);
  navButtonLayout->addWidget(samplesPageButton);
  navButtonLayout->addWidget(popPageButton);
  navButtonLayout->addWidget(litterPageButton);

  navButtonGroup->setLayout(navButtonLayout);

  // Create the load document group
  QGroupBox *loadFileGroup = new QGroupBox();
  QVBoxLayout *loadFileLayout = new QVBoxLayout();
  QLabel *loadFileLabel = new QLabel(tr("<b>File Settings</b>"));
  yearLabel = new QLabel(tr("Dataset Year"));
  regionLabel = new QLabel(tr("Dataset Region"));

  loadFileLayout->addWidget(loadFileLabel);
  loadFileLayout->addWidget(yearLabel);
  loadFileLayout->addWidget(datasetYear);
  loadFileLayout->addWidget(regionLabel);
  loadFileLayout->addWidget(datasetRegion);
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
  fileInfo = new QLabel(tr("Current file: <none>"));
  QStatusBar *status = statusBar();
  status->addWidget(fileInfo);
}

void MainWindow::addFileMenu()
{
  QAction *locAction = new QAction(tr("Set Data &Location"), this);
  locAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_L));
  connect(locAction, SIGNAL(triggered()), this, SLOT(setDataLocation()));

  QAction *closeAction = new QAction(tr("Quit"), this);
  closeAction->setShortcut(QKeySequence::Close);
  connect(closeAction, SIGNAL(triggered()), this, SLOT(close()));

  QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(locAction);
  fileMenu->addAction(closeAction);
}

void MainWindow::addHelpMenu()
{
  QAction *aboutAction = new QAction(tr("&About"), this);
  connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

  QAction *aboutQtAction = new QAction(tr("About &Qt"), this);
  connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

  QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
  helpMenu->addAction(aboutAction);
  helpMenu->addAction(aboutQtAction);
}

void MainWindow::setDataLocation()
{
  QString directory = QFileDialog::getExistingDirectory(
      this, tr("Data Location"), ".",
      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

  if (directory.length() > 0)
  {
    dataLocation = directory;
  }
}

// Ran when load button pressed
void MainWindow::openCSV()
{
  if (dataLocation == "")
  {
    QMessageBox::critical(this, tr("Data Location Error"),
                          tr("Data location has not been set!\n\n"
                             "You can specify this via the File menu."));
    return;
  }

  std::vector<QString> regionCodenames = {
      "CB",
      "CL",
      "DNL",
      "DC",
      "ENS",
      "GMMC",
      "HNL",
      "KSL",
      "LN",
      "NDT",
      "SHWG",
      "SSD",
      "SWWM",
      "W",
      "WT",
      "Y"};

  auto filename = QString("%1-%2.csv")
                      .arg(regionCodenames[datasetRegion->currentIndex()])
                      .arg(datasetYear->currentText());
  auto path = dataLocation + "/" + filename;

  try
  {
    model.updateFromFile(path);
    dataset.loadData(path.toStdString());
  }
  catch (const std::exception &error)
  {
    QMessageBox::critical(this, "CSV File Error", error.what());
    return;
  }

  fileInfo->setText(QString(tr("Current file: <kbd>%1</kbd>")).arg(filename));

  // Send the signal to all child components that the dataset has been updated
  emit datasetUpdated(&dataset);
}

void MainWindow::about()
{
  QMessageBox::about(this, tr("About Pollutants Tool"),
                     tr("Pollutants Tool displays and analyzes water pollutants data loaded from"
                        "a CSV file produced by Defra's Water Quality Archive"
                        "\n\nCreated By:"
                        "\nDaniel Spiers, Wei See, Cheuk Ho, Tommaso Chiti"));
}

void MainWindow::makeConnections()
{
  // Button functionality
  connect(homePageButton, SIGNAL(clicked()), this, SLOT(showHomePage()));
  connect(samplesPageButton, SIGNAL(clicked()), this, SLOT(showSamplesPage()));
  connect(overviewPageButton, SIGNAL(clicked()), this, SLOT(showOverviewPage()));
  connect(popPageButton, SIGNAL(clicked()), this, SLOT(showPOPPage()));
  connect(litterPageButton, SIGNAL(clicked()), this, SLOT(showLitterPage()));

  connect(loadButton, SIGNAL(clicked()), this, SLOT(openCSV()));

  // When dataset is updated
  connect(this, SIGNAL(datasetUpdated(SampleDataset *)), samplesPage, SLOT(updateColumnWidths()));
  connect(this, SIGNAL(datasetUpdated(SampleDataset *)), homePage, SIGNAL(datasetUpdated(SampleDataset *)));
  connect(this, SIGNAL(datasetUpdated(SampleDataset *)), overviewPage, SLOT(updateDataset(SampleDataset *)));
  connect(this, SIGNAL(datasetUpdated(SampleDataset *)), popPage, SLOT(updateDataset(SampleDataset *)));

  // Homepage cards clicked
  connect(homePage, SIGNAL(overviewCardClicked()), this, SLOT(showOverviewPage()));
  connect(homePage, SIGNAL(popCardClicked()), this, SLOT(showPOPPage()));
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

void MainWindow::showPOPPage()
{
  pages->setCurrentIndex(3);
}

void MainWindow::showLitterPage()
{
  pages->setCurrentIndex(4);
}