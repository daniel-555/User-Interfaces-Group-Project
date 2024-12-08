#pragma once

#include <QGroupBox>

class QLabel;
class QChart;
class QPieSeries;
class QPushButton;
class SampleDataset;

class POPCard : public QGroupBox
{
    Q_OBJECT
public:
    POPCard();

signals:
    void clicked();

public slots:
    void updateChart();
    void datasetUpdated(SampleDataset *);

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