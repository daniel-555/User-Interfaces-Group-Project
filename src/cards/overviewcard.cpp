#include <QtWidgets>
#include "overviewcard.hpp"

OverviewCard::OverviewCard()
{
    createWidgets();
    arrangeWidgets();
}

void OverviewCard::createWidgets()
{
    title = new QLabel("<h3>Pollutants Overview</h3>");
}

void OverviewCard::arrangeWidgets()
{
    QVBoxLayout *layout = new QVBoxLayout();

    layout->addWidget(title);
    layout->setAlignment(Qt::AlignTop);

    setLayout(layout);
}