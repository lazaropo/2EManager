#include "combatantwidget.h"

#include "ui_combatantwidget.h"

CombatantWidget::CombatantWidget(pf2e_manager::Combatant* combatant,
                                 QWidget* parent)
    : QWidget(parent), ui(new Ui::CombatantWidget), _combatant(combatant) {
  ui->setupUi(this);

  ui->listWidget_effect->setUI(std::bind(
      &MyMenuWidget::setLayout, ui->listWidget_effect, std::placeholders::_1));

  using namespace pf2e_manager;

  ui->lineEdit_hp_curr->setText(QString::number(_combatant->getHPCurr()));
  ui->lineEdit_hp_max->setText(QString::number(_combatant->getHPMax()));
  ui->lineEdit_hp_tmp->setText(QString::number(_combatant->getHPTmp()));
  // ui->lineEdit_hp_curr->setText(QString::number(_combatant->getHPMax()));

  for (auto it_eff = _combatant->getEffects().begin(),
            it_eff_end = _combatant->getEffects().end();
       it_eff != it_eff_end; ++it_eff) {
    EffectListWidgetItem* item =
        new EffectListWidgetItem(it_eff, QString::number(1));
    item->setText(
        QString("%1 from %2 on %3\tDuration:%4\tValue:%5")
            .arg(QString::fromStdString((*it_eff)->getName()))
            .arg(QString::fromStdString((*it_eff)->getCreator()
                                            ? (*it_eff)->getCreator()->getName()
                                            : "User"))
            .arg(QString::fromStdString((*it_eff)->getObject()->getName()))
            .arg(QString::number((*it_eff)->getDuration()))
            .arg(QString::number((*it_eff)->getValue())));

    ui->listWidget_effect->addItem(item);
  }

  // item->setToolTip(QString::fromStdString((*it_eff)->what()));

  //  it_eff = it->getEffects().begin() + 1;

  //  item =
  //      new EffectListWidgetItem(it_eff, QString::number(1));
  //  item->setText(
  //      QString("%1 from %2 on %3\tDuratoin:%4\tValue:%5")
  //          .arg(QString::fromStdString((*it_eff)->getName()))
  //          .arg(QString::fromStdString((*it_eff)->getCreator()
  //                                          ?
  //                                          (*it_eff)->getCreator()->getName()
  //                                          : "User"))
  //          .arg(QString::fromStdString((*it_eff)->getObject()->getName()))
  //          .arg(QString::number((*it_eff)->getDuration()))
  //          .arg(QString::number((*it_eff)->getValue())));
  //  item->setToolTip(QString::fromStdString((*it_eff)->what()));

  // ui->listWidget_effect->addItem(item);
}

CombatantWidget::~CombatantWidget() { delete ui; }

// void CombatantWidget::on_listWidget_effect_itemEntered(QListWidgetItem*
// item_unused) {
//   QLabel* item = new QLabel();
//   item->setScaledContents(true);
//   item->setMaximumSize(ui->layout_effect->maximumSize().rwidth(),
//   ui->layout_effect->maximumSize().rheight()); auto it_eff =
//   _controller->getCombatants().begin()->getEffects().begin();
//   item->setToolTip(QString("%1").arg(QString::fromStdString((*it_eff)->what())));
//   ui->layout_effect->addWidget(item);
// }

// void CombatantWidget::on_listWidget_effect_itemClicked(QListWidgetItem*
// item_unused) {
//   QLabel* item = new QLabel();
//   item->setScaledContents(true);
//   item->setMaximumSize(ui->layout_effect->maximumSize().rwidth(),
//   ui->layout_effect->maximumSize().rheight()); auto it_eff =
//   _controller->getCombatants().begin()->getEffects().begin();
//   item->setText(QString("%1").arg(QString::fromStdString((*it_eff)->what())));
//   item->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
//   ui->layout_effect->addWidget(item);
// }
