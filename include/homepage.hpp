#pragma once

#include <QWidget>

class OverviewCard;
class POPCard;
class SampleDataset;

class HomePage : public QWidget
{
    Q_OBJECT
public:
    HomePage();

signals:
    void datasetUpdated(SampleDataset *);
    void overviewCardClicked();
    void popCardClicked();

private:
    void createWidgets();
    void arrangeWidgets();
    void makeConnections();

    OverviewCard *overviewCard;
    POPCard *popCard;
    SampleDataset *dataset;
};