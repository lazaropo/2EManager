#include "combatantwidget.h"

#include "ui_combatantwidget.h"

CombatantWidget::CombatantWidget(pf2e_manager::Combatant* combatant,
                                 QWidget* parent)
    : QWidget(parent), ui(new Ui::CombatantWidget), _combatant(combatant) {
  ui->setupUi(this);

  listWidget_effect->setUI(std::bind(&MyMenuWidget::setLayout,
                                     listWidget_effect, std::placeholders::_1));

  using namespace pf2e_manager;

  ui->label_name->setText(QString::fromStdString(_combatant->getName()));
  ui->lineEdit_hp_curr->setText(QString::number(_combatant->getHPCurr()));
  ui->lineEdit_hp_max->setText(QString::number(_combatant->getHPMax()));
  ui->lineEdit_hp_tmp->setText(QString::number(_combatant->getHPTmp()));
  // ui->lineEdit_hp_curr->setText(QString::number(_combatant->getHPMax()));

  for (auto it_eff : _combatant->getEffects() /*= _combatant->getEffects().begin(),
            it_eff_end = _combatant->*/) {
    EffectListWidgetItem* item =
        new EffectListWidgetItem(it_eff, QString::number(1));
    item->setText(
        QString("%1 from %2 on %3\tDuration:%4\tValue:%5")
            .arg(QString::fromStdString((it_eff)->getName()))
            .arg(QString::fromStdString((it_eff)->getCreator()
                                            ? (it_eff)->getCreator()->getName()
                                            : "User"))
            .arg(QString::number((it_eff)->getDuration()))
            .arg(QString::number((it_eff)->getValue())));

    listWidget_effect->addItem(item);
    listWidget_effect->setGeometry(QRect(400, 10, 500, 140));
  }

  setAttribute(Qt::WA_StyledBackground);

  /// updateContent();

  pf2e_manager::SimpleEffectBuilder builder;
  pf2e_manager::EffectDirector director(&builder);
  director.buildConfusedEffect(2, 5);
  builder.setReciever(_combatant);
  builder.setCreator(nullptr);
  _combatant->addEffect(builder.getSimpleEffect());

  //  updateContent();

  director.buildDazzledEffect(1, 4);
  builder.setReciever(_combatant);
  builder.setCreator(nullptr);
  _combatant->addEffect(builder.getSimpleEffect());

  // updateContent();
}

CombatantWidget::~CombatantWidget() { delete ui; }

void CombatantWidget::updateContent() {
  if (!_combatant || !ui || !listWidget_effect) return;

  ui->label_name->setText(QString::fromStdString(_combatant->getName()));
  ui->lineEdit_hp_curr->setText(QString::number(_combatant->getHPCurr()));
  ui->lineEdit_hp_max->setText(QString::number(_combatant->getHPMax()));
  ui->lineEdit_hp_tmp->setText(QString::number(_combatant->getHPTmp()));

  listWidget_effect->clear();
  for (auto it_eff : _combatant->getEffects() /*= _combatant->getEffects().begin(),
            it_eff_end = _combatant->getEffects().end();
       it_eff != it_eff_end; ++it_eff*/) {
    if (!it_eff) break;
    EffectListWidgetItem* item =
        new EffectListWidgetItem(it_eff, QString::number(1));
    item->setText(
        QString("%1 from %2 on %3\tDuration:%4\tValue:%5")
            .arg(QString::fromStdString((it_eff)->getName()))
            .arg(QString::fromStdString((it_eff)->getCreator()
                                            ? (it_eff)->getCreator()->getName()
                                            : "User"))
            .arg(QString::fromStdString((it_eff)->getObject()->getName()))
            .arg(QString::number((it_eff)->getDuration()))
            .arg(QString::number((it_eff)->getValue())));

    listWidget_effect->addItem(item);
  }
}
