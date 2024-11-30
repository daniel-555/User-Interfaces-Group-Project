#pragma once

#include <QWidget>

class HomePage: public QWidget
{
    public:
        HomePage();

    private:
        void createWidgets();
        void arrangeWidgets();
};