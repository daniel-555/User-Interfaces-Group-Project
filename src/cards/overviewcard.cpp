#include <QtWidgets>
#include <QtCharts>
#include <vector>
#include "overviewcard.hpp"
#include "dataset.hpp"

OverviewCard::OverviewCard(SampleDataset *data) : dataset(data)
{
    createWidgets();
    createChart();
    arrangeWidgets();
}

void OverviewCard::createWidgets()
{
    title = new QLabel("<h3>Pollutants Overview</h3>");
}

void OverviewCard::arrangeWidgets()
{
    QVBoxLayout *layout = new QVBoxLayout();
    QChartView *pieChartView = new QChartView(pieChart);

    layout->addWidget(title);
    layout->addWidget(pieChartView);
    layout->setAlignment(Qt::AlignTop);

    setLayout(layout);
}

void OverviewCard::createChart()
{
    pieChart = new QChart();
    chartData = new QPieSeries();

    pieChart->legend()
        ->setAlignment(Qt::AlignRight);

    pieChart->addSeries(chartData);
    pieChart->setTitle("Most Frequent Samples");
}

void OverviewCard::updateChart()
{
    // for (int i = 1; i < 6; i++)
    // {
    //     QPieSlice *slice = new QPieSlice();
    //     slice->setLabel(QString("Determinand %1").arg(i));
    //     slice->setValue(i);

    //     chartData->append(slice);
    // }

    for (std::pair<std::string, int> determinand : dataset->getCommonPollutants())
    {
        QPieSlice *slice = new QPieSlice();
        slice->setLabel(QString::fromStdString(determinand.first));
        slice->setValue(determinand.second);

        chartData->append(slice);
    }

    chartData->setLabelsVisible(true);
}