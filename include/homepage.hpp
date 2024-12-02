#pragma once

#include <QWidget>

class OverviewCard;

class HomePage : public QWidget
{
public:
    HomePage();

private:
    void createWidgets();
    void arrangeWidgets();

    OverviewCard *overviewCard;
};