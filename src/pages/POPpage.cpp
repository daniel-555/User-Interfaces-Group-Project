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

    pcbType = new QComboBox();
}

void POPPage::createChart()
{
    pcbLevelChart = new QChart();

    pcbLevelChart->setTitle("Please Select A PCB");

    xAxis = new QDateTimeAxis();
    xAxis->setTickCount(10);
    xAxis->setTitleText("Sample Date");
    xAxis->setFormat("hh:mm:ss");

    yAxis = new QValueAxis();
    yAxis->setTitleText("Level (ug/l)");
    yAxis->setRange(0, 1);
    yAxis->setTickCount(10);
    yAxis->setLabelFormat("%.3f");

    pcbLevelChart->addAxis(xAxis, Qt::AlignBottom);
    pcbLevelChart->addAxis(yAxis, Qt::AlignLeft);
}

void POPPage::arrangeWidgets()
{
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignTop);

    QChartView *pcbLevelsView = new QChartView(pcbLevelChart);

    layout->addWidget(title);
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
    series->attachAxis(xAxis);
    series->attachAxis(yAxis);

    std::string determinand = pcbType->currentText().toStdString();
    std::vector<Sample *> filteredSamples = dataset->getDeterminandSamples(determinand);

    std::sort(filteredSamples.begin(), filteredSamples.end(), [](const auto &a, const auto &b)
              { return a->getTime() < b->getTime(); });

    QDateTime sampleTime;

    std::vector<int> values;

    for (const auto &sample : filteredSamples)
    {

        // std::cout << "Determinand: " << sample->getDefinition() << " DateTime: " << sample->getTime() << " Result: " << sample->getResult() << std::endl;
        sampleTime = QDateTime::fromString(QString::fromStdString(sample->getTime()), "yyyy-MM-ddThh:mm:ss");
        series->append(sampleTime.toMSecsSinceEpoch(), sample->getResult());
        values.push_back(sample->getResult());
    }

    pcbLevelChart->setTitle(pcbType->currentText());

    yAxis->setRange(0, *std::max_element(values.begin(), values.end()));
}