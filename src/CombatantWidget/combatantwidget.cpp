#include "combatantwidget.h"

#include "ui_combatantwidget.h"

CombatantWidget::CombatantWidget(pf2e_manager::Combatant* combatant,
                                 QWidget* parent)
    : QWidget(parent), ui(new Ui::CombatantWidget), _combatant(combatant) {
  ui->setupUi(this);

  _listWidget_effect->setUI(std::bind(
      &MyMenuWidget::setLayout, _listWidget_effect, std::placeholders::_1));

  using namespace pf2e_manager;

  ui->label_name->setText(QString::fromStdString(_combatant->getName()));
  ui->lineEdit_hp_curr->setText(QString::number(_combatant->getHPCurr()));
  ui->lineEdit_hp_max->setText(QString::number(_combatant->getHPMax()));
  ui->lineEdit_hp_tmp->setText(QString::number(_combatant->getHPTmp()));

  // auto side = _combatant->getSide();
  //  QString text;
  //  if (side == pf2e_manager::Combatant::Side::TEAM)
  //    text = "TEAM";
  //  else if (side == pf2e_manager::Combatant::Side::ENEAMY)
  //    text = "ENEAMY";
  //  else if (side == pf2e_manager::Combatant::Side::OTHER)
  //    text = "OTHER";
  ui->label_side->setText(
      QString::fromStdString(pf2e_manager::Combatant::formattingSide(
          _combatant->getSide(), true, false)));

  // auto vitality = _combatant->getVitality();

  //  if (vitality == pf2e_manager::Combatant::Vitality::ALIVE)
  //    text = "ALIVE";
  //  else if (vitality == pf2e_manager::Combatant::Vitality::DEAD)
  //    text = "DEAD";
  //  else if (vitality == pf2e_manager::Combatant::Vitality::CONSTRUCT)
  //    text = "CONSTRUCT";
  ui->label_vitality->setText(
      QString::fromStdString(pf2e_manager::Combatant::formattingVitality(
          _combatant->getVitality(), true, false)));

  updateContent();

  _listWidget_effect->setGeometry(QRect(500, 20, 600, 140));
  setAttribute(Qt::WA_StyledBackground);
  setFocusPolicy(Qt::NoFocus);
  setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

  QObject::connect(_listWidget_effect, &MyMenuWidget::itemChanged, this,
                   &CombatantWidget::itemChanged);

  QObject::connect(this, &CombatantWidget::enterEvent, this,
                   &CombatantWidget::enterEvent, Qt::DirectConnection);
  QObject::connect(this, &CombatantWidget::leaveEvent, this,
                   &CombatantWidget::leaveEvent, Qt::DirectConnection);
  QObject::connect(
      ui->lineEdit_initiative, &QLineEdit::editingFinished, this, [&]() {
        _combatant->setInitiative(ui->lineEdit_initiative->text().toInt());
      });
}

CombatantWidget::~CombatantWidget() { delete ui; }

void CombatantWidget::updateContent() {
  if (!_combatant || !ui || !_listWidget_effect) return;

  ui->label_name->setText(QString::fromStdString(_combatant->getName()));
  ui->lineEdit_hp_curr->setText(QString::number(_combatant->getHPCurr()));
  ui->lineEdit_hp_max->setText(QString::number(_combatant->getHPMax()));
  ui->lineEdit_hp_tmp->setText(QString::number(_combatant->getHPTmp()));

  ui->lineEdit_initiative->setText(
      QString::number(_combatant->getInitiative()));

  _listWidget_effect->clear();
  int count = 0;
  for (auto it_eff : _combatant->getEffects()) {
    if (!it_eff) break;
    EffectListWidgetItem* item =
        new EffectListWidgetItem(it_eff, QString::number(++count));

    _listWidget_effect->addItem(item);
    QLabel* l = new QLabel();
    l->setText(
        QString("%1 from\t%2"
                // "on %3\t"
                "Duration:%3Value:%4")
            .arg(QString::fromStdString((it_eff)->getName()), -30)
            .arg(QString::fromStdString((it_eff)->getInvoker()
                                            ? (it_eff)->getInvoker()->getName()
                                            : "User"),
                 -30)
            // .arg(QString::fromStdString((it_eff)->getReciever()->getName()))
            .arg(QString::number((it_eff)->getDuration()), -12)
            .arg(QString::number((it_eff)->getValue()), -12));

    if (it_eff->isActive())
      l->setStyleSheet(_label_active_style);
    else
      l->setStyleSheet(_label_disable_style);

    _listWidget_effect->setItemWidget(item, l);
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
