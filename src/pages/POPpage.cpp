#include <QtWidgets>
#include <QtCharts>
#include "POPpage.hpp"
#include "dataset.hpp"
#include "sample.hpp"
#include <vector>

POPPage::POPPage()
{
    createWidgets();
    createChart();
    arrangeWidgets();
    makeConnections();
}

void POPPage::createWidgets()
{
    title = new QLabel("<h1>Persistent Organic Pollutants</h1>");
    pcbTypeLabel = new QLabel("Please select a PCB type to display");
    pcbType = new QComboBox();
}

void POPPage::createChart()
{
    pcbLevelChart = new QChart();
    pcbLevelChart->legend()->hide();
    pcbLevelChart->setTitle("Please Select A PCB");

    xAxis = new QDateTimeAxis();
    yAxis = new QValueAxis();

    pcbLevelChart->addAxis(xAxis, Qt::AlignBottom);
    pcbLevelChart->addAxis(yAxis, Qt::AlignLeft);
}

void POPPage::arrangeWidgets()
{
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignTop);

    QChartView *pcbLevelsView = new QChartView(pcbLevelChart);

    layout->addWidget(title);
    layout->addWidget(pcbTypeLabel);
    layout->addWidget(pcbType);
    layout->addWidget(pcbLevelsView);

    setLayout(layout);
}

void POPPage::makeConnections()
{
    connect(pcbType, SIGNAL(currentIndexChanged(int)), this, SLOT(updateChart()));
}

void POPPage::updateDataset(SampleDataset *data)
{
    dataset = data;

    for (std::string s : dataset->getDeterminands())
    {
        if (s.find("PCB") != std::string::npos)
        {
            pcbType->addItem(QString::fromStdString(s));
        }
    }
}

void POPPage::updateChart()
{
    QLineSeries *series = new QLineSeries();

    pcbLevelChart->removeAllSeries();

    // Fetch the new PCB type's samples
    std::string determinand = pcbType->currentText().toStdString();
    std::vector<Sample *> filteredSamples = dataset->getDeterminandSamples(determinand);

    // Sort samples in ascending time order
    std::sort(filteredSamples.begin(), filteredSamples.end(), [](const auto &a, const auto &b)
              { return a->getTime() < b->getTime(); });

    QDateTime sampleTime;

    std::vector<int> values;

    // add each data point to the series
    for (const auto &sample : filteredSamples)
    {
        sampleTime = QDateTime::fromString(QString::fromStdString(sample->getTime()), "yyyy-MM-ddThh:mm:ss");
        series->append(sampleTime.toMSecsSinceEpoch(), sample->getResult());
        values.push_back(sample->getResult());
    }

    // fetch the oldest and newest sample dates
    QDateTime oldest = QDateTime::fromString(QString::fromStdString(filteredSamples.front()->getTime()), "yyyy-MM-ddthh:mm:ss");
    QDateTime newest = QDateTime::fromString(QString::fromStdString(filteredSamples.back()->getTime()), "yyyy-MM-ddthh:mm:ss");

    pcbLevelChart->setTitle(QString("A line chart to show the variations of %1 levels over time").arg(pcbType->currentText()));

    xAxis->setTickCount(10);
    xAxis->setFormat("dd-MM-yyyy");
    xAxis->setTitleText("Sample Date");

    yAxis->setTitleText("Level (ug/l)");
    yAxis->setTickCount(10);
    yAxis->setLabelFormat("%.3f");

    yAxis->setRange(0, *std::max_element(values.begin(), values.end()));
    xAxis->setRange(oldest, newest);

    pcbLevelChart->addSeries(series);
    series->attachAxis(xAxis);
    series->attachAxis(yAxis);
}