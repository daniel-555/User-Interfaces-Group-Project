#include <QtWidgets>
#include <QtCharts>
#include <vector>
#include "overviewpage.hpp"
#include "dataset.hpp"
#include "sample.hpp"

OverviewPage::OverviewPage()
{
    createWidgets();
    createChart();
    arrangeWidgets();
}

void OverviewPage::createWidgets()
{
    title = new QLabel("<h1>Pollutants Overview</h1>");
    title->setAlignment(Qt::AlignHCenter);
}

void OverviewPage::arrangeWidgets()
{
    QChartView *pollutantLevelsView = new QChartView(pollutantLevels);
    QVBoxLayout *layout = new QVBoxLayout();

    layout->addWidget(title);
    layout->addWidget(pollutantLevelsView);

    setLayout(layout);
}

void OverviewPage::createChart()
{
    pollutantLevels = new QChart();

    pollutantLevels->setTitle("How Pollutant Levels Have Changed Over Time");

    xAxis = new QDateTimeAxis();
    xAxis->setTickCount(10);
    xAxis->setTitleText("Sample Date");
    xAxis->setFormat("hh:mm:ss");

    yAxis = new QValueAxis();
    yAxis->setLabelFormat("%i");
    yAxis->setTitleText("Result");

    pollutantLevels->addAxis(xAxis, Qt::AlignBottom);
    pollutantLevels->addAxis(yAxis, Qt::AlignLeft);
}

void OverviewPage::updateChart()
{

    QLineSeries *series = new QLineSeries();

    QDateTime sampleTime;

    std::vector<Sample *> determinandSamples = dataset->getDeterminandSamples("Nitrite as N");

    for (const auto &sample : determinandSamples)
    {
        sampleTime = QDateTime::fromString(QString::fromStdString(sample->getTime()), Qt::ISODate);
        series->append(sampleTime.currentMSecsSinceEpoch(), sample->getResult());
    }

    // QDateTime now = QDateTime::currentDateTimeUtc();
    // series->append(QDateTime::currentMSecsSinceEpoch(), 6);
    // series->append(QDateTime::currentMSecsSinceEpoch() + 16000, 2);
    // series->append(QDateTime::currentMSecsSinceEpoch() + 4000, 16);

    pollutantLevels->addSeries(series);
    series->attachAxis(xAxis);
    series->attachAxis(yAxis);
}

void OverviewPage::updateDataset(SampleDataset *data)
{
    dataset = data;
    updateChart();
}