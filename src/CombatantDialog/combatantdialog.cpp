#include "combatantdialog.h"

#include "ui_combatantdialog.h"

CombatantDialog::CombatantDialog(pf2e_manager::Combatant** combatant,
                                 QWidget* parent)
    : QDialog(parent), ui(new Ui::CombatantDialog), _combatant(combatant) {
  ui->setupUi(this);
}

CombatantDialog::~CombatantDialog() { delete ui; }

void CombatantDialog::on_pushButton_finish_clicked() {
  pf2e_manager::Combatant::Vitality vit =
      pf2e_manager::Combatant::formattingVitality(
          ui->comboBox_vitality->currentText().toStdString());

  pf2e_manager::Combatant::Side side = pf2e_manager::Combatant::formattingSide(
      ui->comboBox_side->currentText().toStdString());

  *_combatant = new pf2e_manager::Combatant(
      ui->lineEdit_hp->text().toInt(), ui->lineEdit_init->text().toInt(), side,
      ui->lineEdit_name->text().toStdString(), vit);
  accept();
}
