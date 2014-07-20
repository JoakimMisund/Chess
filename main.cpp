#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>


int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  
  MainWindow window;

  Controller c( &window );

  return app.exec();
}
