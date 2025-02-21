#include "EffectDialog.h"

#include "ui_effectdialog.h"

EffectDialog::EffectDialog(pf2e_manager::Controller* unit,
                           pf2e_manager::Combatant* combatant, QWidget* parent)
    : QDialog(parent),
      ui(new Ui::EffectDialog),
      _controller(unit),
      _combatant(combatant) {
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
  ui->comboBox_effect->addItem("Malevolence");
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

  // ui->comboBox_effect->addItem("Other effect");

  //    ui->comboBox_effect->setEditable(true);
  // ui->comboBox_effect->setStyle(QStyle::SH_ComboBox_ListMouseTracking);
  ui->comboBox_effect->setEditable(true);
}

EffectDialog::~EffectDialog() { delete ui; }

void EffectDialog::on_button_set_clicked() {
  if (!_controller || !_combatant) return;
  int duration = ui->lineEdit_duration->text().toInt();
  int value = ui->lineEdit_value->text().toInt();
  if ((!duration && !value) || duration < 0 || value < 0) return;

  std::string effect_name;
  if (ui->comboBox_effect->currentText() == "Persistent Damage")
    effect_name = "effect:persistentdamage";
  else
    effect_name =
        "effect:" + ui->comboBox_effect->currentText().toLower().toStdString();

  _controller->makeEffect(nullptr, _combatant, effect_name, duration, value);
  // _controller = nullptr;
  accept();
  // closeDialog();
}
