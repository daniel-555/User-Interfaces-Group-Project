#pragma once

#include <QWidget>

class OverviewCard;
class SampleDataset;

class HomePage : public QWidget
{
    Q_OBJECT
public:
    HomePage();

signals:
    void datasetUpdated(SampleDataset *);
    void overviewCardClicked();

private:
    void createWidgets();
    void arrangeWidgets();
    void makeConnections();

    OverviewCard *overviewCard;
    SampleDataset *dataset;
};