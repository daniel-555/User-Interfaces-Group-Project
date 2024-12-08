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
    OverviewCard();

signals:
    void clicked();

public slots:
    void datasetUpdated(SampleDataset *);

private:
    void createWidgets();
    void arrangeWidgets();
    void createChart();
    void updateChart();

    QLabel *title;
    QPushButton *showMore;

    QChart *pieChart;
    QPieSeries *chartData;

    SampleDataset *dataset;
};