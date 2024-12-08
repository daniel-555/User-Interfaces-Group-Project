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
    QChartView *pieChartView = new QChartView(pieChart);

    header->addWidget(title);
    header->addWidget(showMore);
    layout->addLayout(header);
    layout->addWidget(pieChartView);
    layout->addWidget(showMore);
    layout->setAlignment(Qt::AlignTop);

    setLayout(layout);
}

void POPCard::createChart()
{
    pieChart = new QChart();
    chartData = new QPieSeries();

    pieChart->legend()
        ->hide();

    pieChart->setTitle("PCB samples");
    pieChart->addSeries(chartData);
}

void POPCard::updateChart()
{
    int frequency = 0;

    std::vector<Sample *> samples;
    QPieSlice *slice;

    for (std::string determinand : dataset->getDeterminands())
    {
        if (determinand.find("PCB") != std::string::npos)
        {
            samples = dataset->getDeterminandSamples(determinand);

            slice = new QPieSlice();
            slice->setLabel(QString::fromStdString(determinand));
            slice->setValue(samples.size());
            chartData->append(slice);
        }
    }

    chartData->setLabelsVisible(true);
}

void POPCard::datasetUpdated(SampleDataset *data)
{
    dataset = data;
    updateChart();
}