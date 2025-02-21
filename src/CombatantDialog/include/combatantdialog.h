#ifndef COMBATANTDIALOG_H
#define COMBATANTDIALOG_H

#include <QDialog>
#include <boost/serialization/export.hpp>

#include "Combatant.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class CombatantDialog;
}
QT_END_NAMESPACE

class CombatantDialog : public QDialog {
  Q_OBJECT

 public:
  CombatantDialog(pf2e_manager::Combatant** combatant,
                  QWidget* parent = nullptr);

  ~CombatantDialog();

 private slots:
  void on_pushButton_finish_clicked();

 private:
  Ui::CombatantDialog* ui;

  pf2e_manager::Combatant** _combatant = nullptr;
};
#endif  // COMBATANTDIALOG_H
