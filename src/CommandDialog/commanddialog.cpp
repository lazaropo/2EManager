#include "commanddialog.h"

#include "ui_commanddialog.h"

CommandDialog::CommandDialog(pf2e_manager::CommandBase **command,
                             pf2e_manager::Controller *controller,
                             QWidget *parent)
    : QDialog(parent),
      ui(new Ui::CommandDialog),

      _controller(controller),
      _command(command) {
  ui->setupUi(this);

  std::list<pf2e_manager::Combatant *> *combatants =
      _controller->getCombatants();
  ui->comboBox_from->addItem(QIcon(), "<user>");

  /*auto*/ layout_to = new QGridLayout();
  int count = 0;
  for (auto it : *combatants) {
    _list.push_back(it);
    QString name = QString::fromStdString(it->getName());

    ui->comboBox_from->addItem(QIcon(), name);

    QHBoxLayout *h_layout = new QHBoxLayout();
    h_layout->setSpacing(0);
    h_layout->setContentsMargins(0, 0, 0, 0);
    QGroupBox *button_group = new QGroupBox();
    button_group->setStyleSheet("border: none;");
    QRadioButton *button = new QRadioButton();
    button->setChecked(true);
    button->setText("0x");
    h_layout->addWidget(button);  // 0x damage
    button = new QRadioButton();
    button->setText("0.5x");
    h_layout->addWidget(button);  // 0.5x damage
    button = new QRadioButton();
    button->setText("1x");
    h_layout->addWidget(button);  // 1x damage
    button = new QRadioButton();
    button->setText("2x");
    h_layout->addWidget(button);  // 2x damage

    button_group->setLayout(h_layout);
    layout_to->addWidget(button_group, count, 0);

    QLabel *text_name = new QLabel();
    text_name->setText(name);
    layout_to->addWidget(text_name, count++, 1);
  }

  ui->scrollAreaWidgetContents->setLayout(layout_to);
}

CommandDialog::~CommandDialog() { delete ui; }

void CommandDialog::on_pushButton_accept_clicked() {
  int value = ui->lineEdit_value->text().toInt();
  // ind - 1 cause box_from starts from "user" variant
  int ind_sender = ui->comboBox_from->currentIndex() - 1;
  int max_count = ui->comboBox_from->count();
  pf2e_manager::SubjectBase *sender;
  if (ind_sender == -1 || ind_sender >= max_count)
    sender = nullptr;
  else
    sender = _list[ind_sender];

  std::vector<std::pair<pf2e_manager::SubjectBase *, int>> info;
  /*QGridLayout*/                   // QLayout *scroll_layout =
  /*qobject_cast<QGridLayout *>(*/  // ui->scrollArea->widget()->layout();
  for (auto i = 0, i_end = layout_to->count() / 2; i < i_end; ++i) {
    auto box = layout_to->itemAt(i * 2 + 0)->widget();
    auto h_layout = box->layout();
    for (int j = 1, j_end = h_layout->count(); j < j_end; ++j) {
      auto check_button =
          qobject_cast<QRadioButton *>(h_layout->itemAt(j)->widget());
      if (check_button->isChecked()) {
        double coeff = 1.;
        if (j == 1)
          coeff = 0.5;
        else if (j == 3)
          coeff = 2.;
        info.push_back(std::pair(_list[i], static_cast<int>(value * coeff)));
        break;
      }
    }
  }
  std::string command_name = "command:";
  if (info.size() > 1) command_name += "mass";

  command_name += ui->comboBox_command->currentText().toStdString();
  if (info.size())
    *_command = _controller->makeCommand(sender, command_name, info);

  accept();
}
