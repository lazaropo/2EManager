#include "combatantdialog.h"
#include "ui_combatantdialog.h"

CombatantDialog::CombatantDialog(pf2e_manager::Combatant** combatant, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CombatantDialog)
    , _combatant(combatant)
{
    ui->setupUi(this);
}

CombatantDialog::~CombatantDialog()
{
    delete ui;
}


void CombatantDialog::on_pushButton_finish_clicked()
{
    pf2e_manager::Combatant::Vitality vit = pf2e_manager::Combatant::Vitality::CONSTRUCT;
    switch (ui->comboBox_vitality->currentIndex()) {
    case 0:
        vit = pf2e_manager::Combatant::Vitality::ALIVE;
        break;
    case 1:
        vit = pf2e_manager::Combatant::Vitality::DEAD;
        break;
    case 2:
        vit = pf2e_manager::Combatant::Vitality::CONSTRUCT;
        break;
    default:
       reject();
    };

    pf2e_manager::Combatant::Side side = pf2e_manager::Combatant::Side::OTHER;
    switch (ui->comboBox_vitality->currentIndex()) {
    case 0:
       side = pf2e_manager::Combatant::Side::TEAM;
       break;
    case 1:
       side = pf2e_manager::Combatant::Side::ENEAMY;
       break;
    case 2:
       side = pf2e_manager::Combatant::Side::OTHER;
       break;
    default:
       reject();
    };

    *_combatant = new pf2e_manager::Combatant(ui->lineEdit_hp->text().toInt(),
                   ui->lineEdit_init->text().toInt(),
                                               side,
                   ui->lineEdit_name->text().toStdString(),
                   vit);
    accept();
}

