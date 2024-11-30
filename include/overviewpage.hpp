#pragma once

#include <QWidget>

class OverviewPage: public QWidget
{
    public:
        OverviewPage();

    private:
        void createWidgets();
        void arrangeWidgets();
};