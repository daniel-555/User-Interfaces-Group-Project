#include <QtWidgets>
#include "homepage.hpp"
#include "overviewcard.hpp"
#include "dataset.hpp"

HomePage::HomePage()
{
    createWidgets();
    arrangeWidgets();
    makeConnections();
}

void HomePage::createWidgets()
{
    overviewCard = new OverviewCard();
}

void HomePage::arrangeWidgets()
{
    QGridLayout *grid = new QGridLayout();

    grid->addWidget(overviewCard, 0, 0);
    grid->addWidget(overviewCard, 1, 0);

    grid->setRowStretch(0, 1);
    grid->setRowStretch(1, 1);

    setLayout(grid);
}

void HomePage::makeConnections()
{
    connect(this, SIGNAL(datasetUpdated(SampleDataset *)), overviewCard, SLOT(datasetUpdated(SampleDataset *)));
    connect(overviewCard, SIGNAL(clicked()), this, SIGNAL(overviewCardClicked()));
}