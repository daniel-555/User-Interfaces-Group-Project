#include <QtWidgets>
#include "homepage.hpp"

HomePage::HomePage()
{
    createWidgets();
    arrangeWidgets();
}

void HomePage::createWidgets()
{
    QLabel* filler = new QLabel("<h1>This is the home page");
    filler->setAlignment(Qt::AlignCenter);

    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(filler);

    setLayout(layout);
}

void HomePage::arrangeWidgets()
{

}