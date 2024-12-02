#pragma once

#include <QWidget>

class OverviewCard;
class SampleDataset;

class HomePage : public QWidget
{
    Q_OBJECT
public:
    HomePage(SampleDataset *);

signals:
    void datasetUpdated();
    void overviewCardClicked();

private:
    void createWidgets();
    void arrangeWidgets();
    void makeConnections();

    OverviewCard *overviewCard;
    SampleDataset *dataset;
};