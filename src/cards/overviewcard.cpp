#include <QtWidgets>
#include <QtCharts>
#include <vector>
#include "overviewcard.hpp"
#include "dataset.hpp"

OverviewCard::OverviewCard()
{
    createWidgets();
    createChart();
    arrangeWidgets();
}

void OverviewCard::createWidgets()
{
    title = new QLabel("<h3>Pollutants Overview</h3>");
    showMore = new QPushButton("Show More");

    showMore->setFlat(true);
    connect(showMore, SIGNAL(clicked()), this, SIGNAL(clicked()));
}

void OverviewCard::arrangeWidgets()
{
    QVBoxLayout *layout = new QVBoxLayout();
    QHBoxLayout *header = new QHBoxLayout();
    QChartView *pieChartView = new QChartView(pieChart);

    header->addWidget(title);
    header->addWidget(showMore);
    layout->addLayout(header);
    layout->addWidget(pieChartView);
    layout->addWidget(showMore);
    layout->setAlignment(Qt::AlignTop);

    setLayout(layout);
}

void OverviewCard::createChart()
{
    pieChart = new QChart();

    pieChart->legend()
        ->hide();

    pieChart->setTitle("10 Most Recorded Determinands");
}

void OverviewCard::updateChart()
{
    pieChart->removeAllSeries();
    chartData = new QPieSeries();

    for (std::pair<std::string, int> determinand : dataset->getCommonPollutants())
    {
        QPieSlice *slice = new QPieSlice();
        slice->setLabel(QString::fromStdString(determinand.first));
        slice->setValue(determinand.second);
        chartData->append(slice);
    }

    chartData->setLabelsVisible(true);
    pieChart->addSeries(chartData);
}

void OverviewCard::datasetUpdated(SampleDataset *data)
{
    dataset = data;
    updateChart();
}