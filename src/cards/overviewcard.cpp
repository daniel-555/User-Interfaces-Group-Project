#include <QtWidgets>
#include <QtCharts>
#include "overviewcard.hpp"

OverviewCard::OverviewCard()
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

    updateChart();
}

void OverviewCard::updateChart()
{
    for (int i = 1; i < 6; i++)
    {
        QPieSlice *slice = new QPieSlice();
        slice->setLabel(QString("Determinand %1").arg(i));
        slice->setValue(i);

        chartData->append(slice);
    }

    // chartData->append("Determinand 1", 5);
    // chartData->append("Determinand 2", 1);
    // chartData->append("Determinand 3", 16);
    // chartData->append("Determinand 4", 3);
    // chartData->append("Determinand 5", 8);
    // chartData->append("Other", 4);
}