#include <QApplication>

#include "combatantdialog.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  pf2e_manager::Combatant *body;
  CombatantDialog w(&body);
  w.show();

  delete body;
  return a.exec();
}
