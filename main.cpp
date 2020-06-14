#include <iostream>

#include <src/ui//window/MainWindow.h>

#include <Qt>
#include <QtWidgets/QApplication>
int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  MainWindow mw;
  return app.exec();
}
