#include <QtWidgets>
#include "homepage.hpp"
#include "overviewcard.hpp"

HomePage::HomePage()
{
    createWidgets();
    arrangeWidgets();
}

void HomePage::createWidgets()
{
    overviewCard = new OverviewCard();
}

void HomePage::arrangeWidgets()
{
    QGridLayout *grid = new QGridLayout();

    grid->addWidget(overviewCard, 0, 0);

    setLayout(grid);
}