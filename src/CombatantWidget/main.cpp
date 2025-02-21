#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "combatantwidget.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QTranslator translator;
  const QStringList uiLanguages = QLocale::system().uiLanguages();
  for (const QString &locale : uiLanguages) {
    const QString baseName = "CombatantWidget_" + QLocale(locale).name();
    if (translator.load(":/i18n/" + baseName)) {
      a.installTranslator(&translator);
      break;
    }
  }
  pf2e_manager::Combatant unit(100, 23, pf2e_manager::Combatant::Side::TEAM,
                               "Peppa");
  pf2e_manager::SimpleEffectBuilder builder;
  pf2e_manager::EffectDirector director(&builder);
  director.buildClumsyEffect(2, 1);
  builder.setReciever(&unit);
  builder.setCreator(nullptr);
  unit.addEffect(builder.getSimpleEffect());

  CombatantWidget w(&unit);
  w.show();
  return a.exec();
}
