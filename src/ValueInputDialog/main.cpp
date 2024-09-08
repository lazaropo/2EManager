#include <QApplication>

#include "valueinputdialog.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  ValueInputDialog w;
  w.show();
  return a.exec();
}
