#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "EffectDialog.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QTranslator translator;
  const QStringList uiLanguages = QLocale::system().uiLanguages();
  for (const QString &locale : uiLanguages) {
    const QString baseName = "EffectWidget_" + QLocale(locale).name();
    if (translator.load(":/i18n/" + baseName)) {
      a.installTranslator(&translator);
      break;
    }
  }
  pf2e_manager::Combatant tmp(100, 233, pf2e_manager::Combatant::Side::ENEAMY,
                              "Peppa");
  EffectDialog w(&tmp);
  w.show();
  return a.exec();
}
