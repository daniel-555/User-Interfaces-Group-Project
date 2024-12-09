#pragma once

#include <QGroupBox>

class QLabel;
class QChart;
class QBarSeries;
class QPushButton;
class SampleDataset;
class QBarCategoryAxis;
class QValueAxis;

class POPCard : public QGroupBox
{
    Q_OBJECT
public:
    POPCard();

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

    QChart *barChart;
    QBarSeries *chartData;

    QBarCategoryAxis *xAxis;
    QValueAxis *yAxis;

    SampleDataset *dataset;
};