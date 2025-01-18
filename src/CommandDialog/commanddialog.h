#ifndef _COMMANDDIALOG_H_
#define _COMMANDDIALOG_H_

#include <QComboBox>
#include <QDialog>
#include <QGridLayout>
#include <QGroupBox>
#include <QRadioButton>

#include "Controller.h"

extern "C" {
#include "../ReversePolishNotation/s21_calc.h"
}
// namespace

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
