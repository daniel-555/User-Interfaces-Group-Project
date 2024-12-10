#include <QtWidgets>
#include <QtCharts>
#include "litterpage.hpp"
#include "dataset.hpp"

LitterPage::LitterPage()
{
    createWidgets();
    createCharts();
    arrangeWidgets();

    updatePlasticChart();
    updateTarryChart();
    updateSewageChart();
}

void LitterPage::createWidgets()
{
    plasticBox = new QGroupBox();
    plasticTitle = new QLabel(tr("<h3>Bathing Water Profile : Other Litter (plastics)</h3>"));

    tarryBox = new QGroupBox();
    tarryTitle = new QLabel(tr("<h3>Tarry Residues</h3>"));

    sewageBox = new QGroupBox();
    sewageTitle = new QLabel(tr("<h3>Sewage Debris</h3>"));
}

void LitterPage::createCharts()
{
    plasticBarChart = new QChart();
    plasticBarChart->setTitle("Plastic Litter Bar Chart");
    plasticBarChart->legend()->setAlignment(Qt::AlignBottom);

    tarryPieChart = new QChart();
    tarryPieChart->setTitle("Tarry Residues Pie Chart");
    tarryPieChart->legend()->setAlignment(Qt::AlignRight);

    sewageBarChart = new QChart();
    sewageBarChart->setTitle("Sewage Debris Bar Chart");
}

void LitterPage::arrangeWidgets()
{
    // Arrange plastic box contents
    QVBoxLayout *plasticLayout = new QVBoxLayout();
    QChartView *plasticChartView = new QChartView(plasticBarChart);
    plasticLayout->setAlignment(Qt::AlignTop);
    plasticLayout->addWidget(plasticTitle);
    plasticLayout->addWidget(plasticChartView);
    plasticBox->setLayout(plasticLayout);

    // Arrange tarry residues box contents
    QVBoxLayout *tarryLayout = new QVBoxLayout();
    QChartView *tarryChartView = new QChartView(tarryPieChart);
    tarryLayout->setAlignment(Qt::AlignTop);
    tarryLayout->addWidget(tarryTitle);
    tarryLayout->addWidget(tarryChartView);
    tarryBox->setLayout(tarryLayout);

    // Arrange sewage debris box contents
    QVBoxLayout *sewageLayout = new QVBoxLayout();
    QChartView *sewageChartView = new QChartView(sewageBarChart);
    sewageLayout->setAlignment(Qt::AlignTop);
    sewageLayout->addWidget(sewageTitle);
    sewageLayout->addWidget(sewageChartView);
    sewageBox->setLayout(sewageLayout);

    QGridLayout *layout = new QGridLayout();

    layout->addWidget(tarryBox, 0, 0);
    layout->addWidget(sewageBox, 0, 1);
    layout->addWidget(plasticBox, 1, 0, 1, 2);

    layout->setRowStretch(0, 1);
    layout->setRowStretch(1, 1);
    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 1);

    setLayout(layout);
}

void LitterPage::updatePlasticChart()
{
    auto set0 = new QBarSet("DANES DYKE");
    auto set1 = new QBarSet("FRAISTHORPE");
    auto set2 = new QBarSet("BRIDLINGTON");

    *set0 << 1 << 2 << 3 << 4 << 5 << 6 << 6 << 5 << 4 << 3 << 2 << 1;
    *set1 << 5 << 0 << 0 << 4 << 0 << 7 << 4 << 2 << 6 << 0 << 1 << 4;
    *set2 << 3 << 5 << 8 << 13 << 8 << 5 << 3 << 2 << 1 << 7 << 6 << 3;

    QBarSeries *plasticData = new QBarSeries();
    plasticData->append(set0);
    plasticData->append(set1);
    plasticData->append(set2);

    plasticBarChart->addSeries(plasticData);

    QStringList categories{"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    auto xAxis = new QBarCategoryAxis;
    xAxis->append(categories);
    plasticBarChart->addAxis(xAxis, Qt::AlignBottom);
    plasticData->attachAxis(xAxis);

    auto yAxis = new QValueAxis;
    yAxis->setRange(0, 15);
    plasticBarChart->addAxis(yAxis, Qt::AlignLeft);
    plasticData->attachAxis(yAxis);
}

void LitterPage::updateTarryChart()
{
    QPieSeries *tarryData = new QPieSeries();

    std::vector<std::pair<QString, int>> data = {
        {"CAYTON BAY", 11},
        {"REIGHTON", 20},
        {"HORNSEA", 20},
        {"WHITBY", 21},
        {"SANDSEND", 24},
        {"FILEY", 6},
        {"RUNSWICK BAY", 16}};

    for (auto &s : data)
    {
        QPieSlice *slice = new QPieSlice(s.first, s.second);
        tarryData->append(slice);
    }

    tarryPieChart->addSeries(tarryData);
}

void LitterPage::updateSewageChart()
{
    auto set0 = new QBarSet("KNARESBOROUGH");
    auto set1 = new QBarSet("WILSTHORPE");

    *set0 << 1 << 2 << 3 << 4 << 5 << 6;
    *set1 << 5 << 0 << 0 << 4 << 0 << 7;

    auto series = new QHorizontalBarSeries;
    series->append(set0);
    series->append(set1);

    sewageBarChart->addSeries(series);

    QStringList categories{"Jan", "Mar", "May", "Jul", "Sep", "Nov"};
    auto yAxis = new QBarCategoryAxis;
    yAxis->append(categories);
    sewageBarChart->addAxis(yAxis, Qt::AlignLeft);
    series->attachAxis(yAxis);

    auto xAxis = new QValueAxis;
    sewageBarChart->addAxis(xAxis, Qt::AlignBottom);
    series->attachAxis(xAxis);
    xAxis->applyNiceNumbers();
}

void LitterPage::updateDataset(SampleDataset *data)
{
    dataset = data;
}