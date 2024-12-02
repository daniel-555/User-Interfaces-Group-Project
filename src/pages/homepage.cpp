#include <QtWidgets>
#include "homepage.hpp"
#include "overviewcard.hpp"
#include "dataset.hpp"

HomePage::HomePage(SampleDataset *data) : dataset(data)
{
    createWidgets();
    arrangeWidgets();
    makeConnections();
}

void HomePage::createWidgets()
{
    overviewCard = new OverviewCard(dataset);
}

void HomePage::arrangeWidgets()
{
    QGridLayout *grid = new QGridLayout();

    grid->addWidget(overviewCard, 0, 0);

    setLayout(grid);
}

void HomePage::makeConnections()
{
    connect(this, SIGNAL(datasetUpdated()), overviewCard, SLOT(updateChart()));
}