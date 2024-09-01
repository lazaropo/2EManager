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

  ui->label_side->setText(
      QString::fromStdString(pf2e_manager::Combatant::formattingSide(
          _combatant->getSide(), true, false)));

  ui->label_vitality->setText(
      QString::fromStdString(pf2e_manager::Combatant::formattingVitality(
          _combatant->getVitality(), true, false)));

  updateContent();

  _listWidget_effect->setGeometry(QRect(480, 7, 610, 140));
  _listWidget_effect->setStyleSheet(
      "QListWidget{"
      "font: 16px;"
      "color: black;"
      "border-radius: 5px;"
      "background-color: rgb(162, 162, 208);"
      "}");

  setAttribute(Qt::WA_StyledBackground);
  setFocusPolicy(Qt::NoFocus);
  setFixedSize(1110, 155);
  setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

  QObject::connect(_listWidget_effect, &MyMenuWidget::itemChanged, this,
                   &CombatantWidget::itemChanged);

  QObject::connect(
      ui->lineEdit_initiative, &QLineEdit::editingFinished, this, [&]() {
        _combatant->setInitiative(ui->lineEdit_initiative->text().toInt());
      });

  setAcceptDrops(true);

  setBaseStyle();
}

CombatantWidget::~CombatantWidget() { delete ui; }

void CombatantWidget::updateContent() {
  if (!_combatant || !ui || !_listWidget_effect) return;

  ui->label_name->setText(QString::fromStdString(_combatant->getName()));
  ui->lineEdit_hp_curr->setText(QString::number(_combatant->getHPCurr()));
  ui->lineEdit_hp_max->setText(QString::number(_combatant->getHPMax()));

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
        QString("%1from %2"
                "Duration:%3Value:%4")
            .arg(QString::fromStdString((it_eff)->getName()), -25)
            .arg(QString::fromStdString((it_eff)->getInvoker()
                                            ? (it_eff)->getInvoker()->getName()
                                            : "User"),
                 -25)
            .arg(QString::number((it_eff)->getDuration()), -12)
            .arg(QString::number((it_eff)->getValue()), -12));

    if (it_eff->isActive())
      l->setStyleSheet(_label_active_style);
    else
      l->setStyleSheet(_label_disable_style);

    _listWidget_effect->setItemWidget(item, l);
  }
}
