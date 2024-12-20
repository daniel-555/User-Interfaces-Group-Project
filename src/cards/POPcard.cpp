#include <QtWidgets>
#include <QtCharts>
#include <vector>
#include "POPcard.hpp"
#include "dataset.hpp"

POPCard::POPCard()
{
    createWidgets();
    createChart();
    arrangeWidgets();
}

void POPCard::createWidgets()
{
    title = new QLabel("<h3>Persistant Organic Pollutants</h3>");
    showMore = new QPushButton("Show More");

    showMore->setFlat(true);
    connect(showMore, SIGNAL(clicked()), this, SIGNAL(clicked()));
}

void POPCard::arrangeWidgets()
{
    QVBoxLayout *layout = new QVBoxLayout();
    QHBoxLayout *header = new QHBoxLayout();
    QChartView *barChartView = new QChartView(barChart);

    header->addWidget(title);
    header->addWidget(showMore);
    layout->addLayout(header);
    layout->addWidget(barChartView);
    layout->addWidget(showMore);
    layout->setAlignment(Qt::AlignTop);

    setLayout(layout);
}

void POPCard::createChart()
{
    barChart = new QChart();
    chartData = new QBarSeries();

    barChart->legend()
        ->hide();

    xAxis = new QBarCategoryAxis();
    barChart->addAxis(xAxis, Qt::AlignBottom);

    yAxis = new QValueAxis();
    barChart->addAxis(yAxis, Qt::AlignLeft);

    barChart->setTitle("Number of Samples From Each PCB Type");
}

void POPCard::updateChart()
{
    barChart->removeAllSeries();
    chartData = new QBarSeries();

    std::vector<Sample *> samples;
    std::vector<int> freq;

    QStringList categories = {};
    QBarSet *frequencies = new QBarSet("PCB sample frequencies");

    // Find determinands from the dataset containing PCB in their name
    for (std::string determinand : dataset->getDeterminands())
    {
        if (determinand.find("PCB") != std::string::npos)
        {
            // Add the sample's frequency to the bar chart
            samples = dataset->getDeterminandSamples(determinand);
            categories.append(QString::fromStdString(determinand));
            frequencies->append(samples.size());
            freq.push_back(samples.size());
        }
    }
    chartData->append(frequencies);
    barChart->addSeries(chartData);

    xAxis->append(categories);
    chartData->attachAxis(xAxis);

    yAxis->setRange(0, *std::max_element(freq.begin(), freq.end()));
    chartData->attachAxis(yAxis);
}

void POPCard::datasetUpdated(SampleDataset *data)
{
    dataset = data;
    updateChart();
}