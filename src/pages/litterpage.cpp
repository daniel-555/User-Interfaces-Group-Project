#include <QtWidgets>
#include <QtCharts>
#include "litterpage.hpp"
#include "dataset.hpp"

LitterPage::LitterPage()
{
    createWidgets();
    createCharts();
    arrangeWidgets();
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

    tarryPieChart = new QChart();
    tarryPieChart->setTitle("Tarry Residues Pie Chart");

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
}

void LitterPage::updateTarryChart()
{
}

void LitterPage::updateSewageChart()
{
}

void LitterPage::updateDataset(SampleDataset *data)
{
    dataset = data;
}