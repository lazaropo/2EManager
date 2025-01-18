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

  pf2e_manager::utility::t_combatant_container *combatants =
      _controller->getCombatants();
  ui->comboBox_from->addItem(QIcon(), "<user>");

  layout_to = new QGridLayout();

  QLabel *text_coeffs = new QLabel();
  text_coeffs->setText("0x   0.5x   1x   2x");
  text_coeffs->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  layout_to->addWidget(text_coeffs, 0, 0);

  int count = 1;
  pf2e_manager::Combatant *current_combatant = _controller->getCurrent();
  for (auto it : *combatants) {
    _list.push_back(it);
    QString name = QString::fromStdString(it->getName());

    ui->comboBox_from->addItem(QIcon(), name);
    if (it == current_combatant) ui->comboBox_from->setCurrentIndex(count);

    QHBoxLayout *h_layout = new QHBoxLayout();
    h_layout->setSpacing(5);
    h_layout->setContentsMargins(0, 0, 0, 0);
    QGroupBox *button_group = new QGroupBox();
    button_group->setStyleSheet("border: none;");
    QRadioButton *button = new QRadioButton();
    button->setChecked(true);
    button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    // button->setText("0x");
    h_layout->addWidget(button);  // 0x damage
    button = new QRadioButton();
    button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    // button->setText("0.5x");
    h_layout->addWidget(button);  // 0.5x damage
    button = new QRadioButton();
    button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    // button->setText("1x");
    h_layout->addWidget(button);  // 1x damage
    button = new QRadioButton();
    button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    // button->setText("2x");
    h_layout->addWidget(button);  // 2x damage

    button_group->setLayout(h_layout);
    layout_to->addWidget(button_group, count, 0);

    QLabel *text_name = new QLabel();
    text_name->setText(name);
    text_name->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    layout_to->addWidget(text_name, count++, 1);
  }

  ui->scrollAreaWidgetContents->setLayout(layout_to);
}

CommandDialog::~CommandDialog() { delete ui; }

void CommandDialog::on_pushButton_accept_clicked() {
  double value = 0;
  std::wstring w_arr = ui->lineEdit_value->text().toStdWString();
  if (s21_is_expression_correct(w_arr.c_str()) == false)
    s21_main_calc_function(w_arr.c_str(), &value, 0);
  else
    return;
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
  for (auto i = 1, i_end = max_count; i < i_end; ++i) {
    auto box = layout_to->itemAtPosition(i, 0)->widget();
    auto h_layout = box->layout();
    // if (!h_layout) continue;
    for (int j = 1, j_end = h_layout->count(); j < j_end; ++j) {
      auto check_button =
          qobject_cast<QRadioButton *>(h_layout->itemAt(j)->widget());
      if (check_button->isChecked()) {
        double coeff = 1.;
        if (j == 1)
          coeff = 0.5;
        else if (j == 3)
          coeff = 2.;
        info.push_back(std::pair(
            _list[i - 1], static_cast<int>(static_cast<int>(value) * coeff)));
        break;
      }
    }
  }
  std::string command_name = "command:";
  if (info.size() > 1) command_name += "mass";

  command_name += ui->comboBox_command->currentText().toStdString();
  if (info.size())
    *_command = _controller->makeCommand(sender, command_name, info);
  else
    *_command = nullptr;

  accept();
}
