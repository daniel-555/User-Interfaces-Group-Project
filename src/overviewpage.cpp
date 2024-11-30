#include <QtWidgets>
#include "overviewpage.hpp"

OverviewPage::OverviewPage()
{
    createWidgets();
    arrangeWidgets();
}

void OverviewPage::createWidgets()
{
    QLabel* filler = new QLabel("<h1>This is the overview page");
    filler->setAlignment(Qt::AlignCenter);

    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(filler);

    setLayout(layout);
}

void OverviewPage::arrangeWidgets()
{

}