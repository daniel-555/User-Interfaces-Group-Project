// application entry point

#include <QtWidgets>
#include "window.hpp"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  MainWindow window;
  window.show();

  return app.exec();
}
