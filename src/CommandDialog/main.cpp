#include <QApplication>

#include "commanddialog.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  CommandDialog w;
  w.show();
  return a.exec();
}
