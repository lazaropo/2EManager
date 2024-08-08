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

  auto side = _combatant->getSide();
  QString text;
  if (side == pf2e_manager::Combatant::Side::TEAM)
    text = "TEAM";
  else if (side == pf2e_manager::Combatant::Side::ENEAMY)
    text = "ENEAMY";
  else if (side == pf2e_manager::Combatant::Side::OTHER)
    text = "OTHER";
  ui->label_side->setText(text);

  auto vitality = _combatant->getVitality();
  if (vitality == pf2e_manager::Combatant::Vitality::ALIVE)
    text = "ALIVE";
  else if (vitality == pf2e_manager::Combatant::Vitality::DEAD)
    text = "DEAD";
  else if (vitality == pf2e_manager::Combatant::Vitality::CONSTRUCT)
    text = "CONSTRUCT";
  ui->label_vitality->setText(text);

  for (auto it_eff : _combatant->getEffects() /*= _combatant->getEffects().begin(),
            it_eff_end = _combatant->*/) {
    EffectListWidgetItem* item =
        new EffectListWidgetItem(it_eff, QString::number(1));
    item->setText(
        QString("%1 from %2 on %3\tDuration:%4\tValue:%5")
            .arg(QString::fromStdString((it_eff)->getName()))
            .arg(QString::fromStdString((it_eff)->getInvoker()
                                            ? (it_eff)->getInvoker()->getName()
                                            : "User"))
            .arg(QString::fromStdString((it_eff)->getReciever()->getName()))
            .arg(QString::number((it_eff)->getDuration()))
            .arg(QString::number((it_eff)->getValue())));

    listWidget_effect->addItem(item);
  }

  listWidget_effect->setGeometry(QRect(500, 20, 500, 140));
  setAttribute(Qt::WA_StyledBackground);
  setFocusPolicy(Qt::NoFocus);
  setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

  QObject::connect(this, &CombatantWidget::enterEvent, this,
                   &CombatantWidget::enterEvent, Qt::DirectConnection);
  QObject::connect(this, &CombatantWidget::leaveEvent, this,
                   &CombatantWidget::leaveEvent, Qt::DirectConnection);
}

CombatantWidget::~CombatantWidget() { delete ui; }

void CombatantWidget::updateContent() {
  if (!_combatant || !ui || !listWidget_effect) return;

  ui->label_name->setText(QString::fromStdString(_combatant->getName()));
  ui->lineEdit_hp_curr->setText(QString::number(_combatant->getHPCurr()));
  ui->lineEdit_hp_max->setText(QString::number(_combatant->getHPMax()));
  ui->lineEdit_hp_tmp->setText(QString::number(_combatant->getHPTmp()));

  listWidget_effect->clear();
  for (auto it_eff : _combatant->getEffects()) {
    if (!it_eff) break;
    EffectListWidgetItem* item =
        new EffectListWidgetItem(it_eff, QString::number(1));
    item->setText(
        QString("%1 from %2 on %3\tDuration:%4\tValue:%5")
            .arg(QString::fromStdString((it_eff)->getName()))
            .arg(QString::fromStdString((it_eff)->getInvoker()
                                            ? (it_eff)->getInvoker()->getName()
                                            : "User"))
            .arg(QString::fromStdString((it_eff)->getReciever()->getName()))
            .arg(QString::number((it_eff)->getDuration()))
            .arg(QString::number((it_eff)->getValue())));

    listWidget_effect->addItem(item);
  }
}

// void CombatantWidget::enterEvent(QEnterEvent* event) {
//   Q_UNUSED(event);
//   setHoverStyle();
// }

// void CombatantWidget::leaveEvent(QEvent* event) {
//   Q_UNUSED(event);
//   if (style() == _hover_style) setBaseStyle();
// }

// void CombatantWidget::dragEnterEvent(QDragEnterEvent* event) {
//   Q_UNUSED(event);
//   setStyleSheet("CombatantWidget{ background-color:  green;  };");
// }

// void CombatantWidget::dragLeaveEvent(QDragLeaveEvent* event) {
//   Q_UNUSED(event);
//   setStyleSheet("CombatantWidget{ background-color:  rgb(0,0,0);  };");
// }
