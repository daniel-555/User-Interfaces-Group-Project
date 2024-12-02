#pragma once

#include <QGroupBox>

class OverviewCard : public QGroupBox
{
public:
    OverviewCard();

private:
    void createWidgets();
    void arrangeWidgets();

    QLabel *title;
};