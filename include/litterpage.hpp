#pragma once

#include <QWidget>

class SampleDataset;

class LitterPage : public QWidget
{
    Q_OBJECT

public:
    LitterPage();

public slots:
    void updateDataset(SampleDataset *);

private:
    void createWidgets();
    void arrangeWidgets();

    SampleDataset *dataset;
};