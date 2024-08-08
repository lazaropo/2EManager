#ifndef _EFFECTDIALOG_H
#define _EFFECTDIALOG_H

#include <QDialog>
#include <QPushButton>

#include "../Model/Controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class EffectDialog;
}
QT_END_NAMESPACE

class EffectDialog : public QDialog {
  Q_OBJECT

 public:
  EffectDialog(pf2e_manager::Controller* controller,
               pf2e_manager::Combatant* combatant, QWidget* parent = nullptr);
  ~EffectDialog();

  // void closeDialog() { this->accept(); }

 protected:
 private slots:
  void on_button_set_clicked();

 private:
  Ui::EffectDialog* ui;

  pf2e_manager::Controller* _controller;
  pf2e_manager::Combatant* _combatant;
};
#endif  // EFFECTDIALOG_H
