#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "managerwidget.h"

int main(int argc, char *argv[]) {
  int ret = 0;
  try {
    std::set_terminate(&my_terminate_handler);
    // make_logger_record();
    QApplication a(argc, argv);
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
      const QString baseName = "ManagerPF2E_" + QLocale(locale).name();
      if (translator.load(":/i18n/" + baseName)) {
        a.installTranslator(&translator);
        break;
      }
    }
    ManagerWidget w;
    w.show();
    ret = a.exec();
  } catch (std::exception &ex) {
    print_log(ex);
  }
  return ret;
}
