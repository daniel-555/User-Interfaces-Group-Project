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

signals:
    void clicked();

public slots:
    void updateChart();

private:
    void createWidgets();
    void arrangeWidgets();
    void createChart();

    QLabel *title;
    QPushButton *showMore;

    QChart *pieChart;
    QPieSeries *chartData;

    SampleDataset *dataset;
};