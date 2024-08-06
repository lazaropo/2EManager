#include <QApplication>

#include "commandicon.h"

int main(int argc, char *argv[]) {
  Q_INIT_RESOURCE(resource);
  QApplication a(argc, argv);
  CommandIcon w(nullptr);
  w.show();
  return a.exec();
}
