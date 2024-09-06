#ifndef COMMANDDIALOG_H
#define COMMANDDIALOG_H

#include <QComboBox>
#include <QDialog>
#include <QGridLayout>
#include <QGroupBox>
#include <QRadioButton>

#include "../Model/Controller.h"

extern "C" {
// #ifndef MYLIB_STATIC_DEFINE
// #include "../ReversePolishNotation/s21_calc_static.h" // __PATH_REVERSE_POLISH_NOTATION__
// #else
// #include "../ReversePolishNotation/s21_calc_shared.h" // __PATH_REVERSE_POLISH_NOTATION__
// #endif
#include "../ReversePolishNotation/s21_calc.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class CommandDialog;
}
QT_END_NAMESPACE

class CommandDialog : public QDialog {
  Q_OBJECT

 public:
  CommandDialog(pf2e_manager::CommandBase **command,
                pf2e_manager::Controller *controller,
                QWidget *parent = nullptr);
  ~CommandDialog();

 private slots:
  void on_pushButton_accept_clicked();

 private:
  Ui::CommandDialog *ui;
  QList<pf2e_manager::Combatant *> _list;

  pf2e_manager::Controller *_controller;
  pf2e_manager::CommandBase **_command;

  QGridLayout *layout_to = nullptr;
};
#endif  // COMMANDDIALOG_H
