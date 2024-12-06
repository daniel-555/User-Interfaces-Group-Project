#pragma once

#include <QWidget>

class SampleDataset;

class POPPage : public QWidget
{
    Q_OBJECT

public:
    POPPage();

public slots:
    void updateDataset(SampleDataset *);

private:
    void createWidgets();
    void arrangeWidgets();

    SampleDataset *dataset;
};