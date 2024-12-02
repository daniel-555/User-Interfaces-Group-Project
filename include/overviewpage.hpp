#pragma once

#include <QWidget>

class QLabel;
class QChart;
class QDateTimeAxis;
class QValueAxis;
class QLineSeries;
class SampleDataset;

class OverviewPage : public QWidget
{
    Q_OBJECT
public:
    OverviewPage();

private:
    void createWidgets();
    void arrangeWidgets();
    void createChart();

    QLabel *title;
    QChart *pollutantLevels;

    QDateTimeAxis *xAxis;
    QValueAxis *yAxis;

    SampleDataset *dataset;

private slots:
    void updateChart();
    void updateDataset(SampleDataset *);
};