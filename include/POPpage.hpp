#pragma once

#include <QWidget>

class SampleDataset;
class QComboBox;
class QLabel;

class QChart;
class QDateTimeAxis;
class QValueAxis;
class QLineSeries;

class POPPage : public QWidget
{
    Q_OBJECT

public:
    POPPage();

public slots:
    void updateDataset(SampleDataset *);

private:
    void createWidgets();
    void createChart();
    void arrangeWidgets();
    void makeConnections();

    QLabel *title;
    QComboBox *pcbType;

    QChart *pcbLevelChart;

    QDateTimeAxis *xAxis;
    QValueAxis *yAxis;

    SampleDataset *dataset;

private slots:
    void updateChart();
};