#pragma once

#include <QWidget>

class SampleDataset;
class QGroupBox;
class QLabel;
class QChart;

class LitterPage : public QWidget
{
    Q_OBJECT

public:
    LitterPage();

public slots:
    void updateDataset(SampleDataset *);

private:
    void createWidgets();
    void createCharts();
    void arrangeWidgets();
    void updateBoxContent();

    void updatePlasticChart();
    void updateTarryChart();
    void updateSewageChart();

    QGroupBox *plasticBox;
    QLabel *plasticTitle;
    QChart *plasticBarChart;

    QGroupBox *tarryBox;
    QLabel *tarryTitle;
    QChart *tarryPieChart;

    QGroupBox *sewageBox;
    QLabel *sewageTitle;
    QChart *sewageBarChart;

    SampleDataset *dataset;
};