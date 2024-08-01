#include "EffectDialog.h"

#include "ui_effectdialog.h"

EffectDialog::EffectDialog(pf2e_manager::Combatant* unit, QWidget* parent)
    : QDialog(parent), ui(new Ui::EffectDialog), _unit(unit) {
  ui->setupUi(this);

  ui->comboBox_effect->addItem("Clumsy");
  ui->comboBox_effect->addItem("Consealed");
  ui->comboBox_effect->addItem("Confused");
  ui->comboBox_effect->addItem("Controlled");
  ui->comboBox_effect->addItem("Dazzled");
  ui->comboBox_effect->addItem("Deafned");
  ui->comboBox_effect->addItem("Doomed");
  ui->comboBox_effect->addItem("Drained");
  ui->comboBox_effect->addItem("Dying");
  ui->comboBox_effect->addItem("Encumbered");

  ui->comboBox_effect->addItem("Enfeebled");
  ui->comboBox_effect->addItem("Fascinated");
  ui->comboBox_effect->addItem("Fatigued");
  ui->comboBox_effect->addItem("Fleeing");
  ui->comboBox_effect->addItem("Frightened");
  ui->comboBox_effect->addItem("Grabbed");
  ui->comboBox_effect->addItem("Hidden");
  ui->comboBox_effect->addItem("Immobilized");
  ui->comboBox_effect->addItem("Indifferent");
  ui->comboBox_effect->addItem("Invisible");

  ui->comboBox_effect->addItem("Observed");
  ui->comboBox_effect->addItem("Off-Guard");
  ui->comboBox_effect->addItem("Paralyzed");
  ui->comboBox_effect->addItem("Persistent Damage");
  ui->comboBox_effect->addItem("Petrified");
  ui->comboBox_effect->addItem("Prone");
  ui->comboBox_effect->addItem("Quickened");
  ui->comboBox_effect->addItem("Restrained");
  ui->comboBox_effect->addItem("Sickened");
  ui->comboBox_effect->addItem("Slowed");

  ui->comboBox_effect->addItem("Stunned");
  ui->comboBox_effect->addItem("Stupefied");
  ui->comboBox_effect->addItem("Unconscious");
  ui->comboBox_effect->addItem("Undetected");
  ui->comboBox_effect->addItem("Unnoticed");
  ui->comboBox_effect->addItem("Wounded");

  ui->comboBox_effect->addItem("Other effect");

  //    ui->comboBox_effect->setEditable(true);
  // ui->comboBox_effect->setStyle(QStyle::SH_ComboBox_ListMouseTracking);
  ui->comboBox_effect->setEditable(true);
}

EffectDialog::~EffectDialog() {
  delete ui;
  //  delete _director;
  //  delete _builder;
}

void EffectDialog::on_button_set_clicked() {
  if (!_unit) return;
  pf2e_manager::SimpleEffectBuilder builder;
  pf2e_manager::EffectDirector director(&builder);

  director.buildEffectByName(
      "effect:" + ui->comboBox_effect->currentText().toLower().toStdString(),
      ui->lineEdit_duration->text().toInt(),
      ui->lineEdit_value->text().toInt());
  builder.setCreator(nullptr);
  builder.setReciever(_unit);

  _unit->addEffect(builder.getSimpleEffect());
  _unit = nullptr;
  // closeDialog();
}
