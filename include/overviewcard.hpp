#pragma once

#include <QGroupBox>

class QLabel;
class QChart;
class QPieSeries;
class QPushButton;
class SampleDataset;

class OverviewCard : public QGroupBox
{
    Q_OBJECT
public:
    OverviewCard(SampleDataset *);

public slots:
    void updateChart();

private:
    void createWidgets();
    void arrangeWidgets();
    void createChart();

    QLabel *title;
    QPushButton *test;

    QChart *pieChart;
    QPieSeries *chartData;

    SampleDataset *dataset;
};