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

  std::list<pf2e_manager::Combatant> combatants = _controller->getCombatants();
  ui->comboBox_from->addItem(QIcon(), "<user>");
  for (auto it : combatants) {
    _list.push_back(&it);
    ui->comboBox_from->addItem(QIcon(), QString::fromStdString(it.getName()));
    ui->comboBox_to->addItem(QIcon(), QString::fromStdString(it.getName()));
  }
}

CommandDialog::~CommandDialog() { delete ui; }

void CommandDialog::on_pushButton_accept_clicked() {
  // ind - 1 cause box_from starts from "user" variant
  int ind_sender = ui->comboBox_from->currentIndex() - 1;
  pf2e_manager::SubjectBase *sender;
  if (ind_sender == -1)
    sender = nullptr;
  else
    sender = _list[ind_sender];

  int ind_reciever = ui->comboBox_to->currentIndex();
  auto reciever = _list[ind_reciever];

  if (reciever && (QString::fromStdString(reciever->getName()) !=
                   ui->comboBox_to->currentText()))
    throw std::logic_error(
        "CommandDialog: reciever by index and by next is not the same.");

  *_command = _controller->makeCommand(
      sender, reciever,
      "command:" + ui->comboBox_command->currentText().toStdString(),
      ui->lineEdit_value->text().toInt());

  accept();
}
