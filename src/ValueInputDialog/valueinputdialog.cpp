#include "valueinputdialog.h"

#include "ui_valueinputdialog.h"

ValueInputDialog::ValueInputDialog(int *ret_value,
                                   const std::string &invoker_name,
                                   const std::string &reciever_name,
                                   const std::string &subject_name,
                                   QWidget *parent)
    : QDialog(parent), ui(new Ui::ValueInputDialog), _ret_value(ret_value) {
  ui->setupUi(this);

  ui->label_from_name->setText(QString::fromStdString(invoker_name));
  ui->label_to_name->setText(QString::fromStdString(reciever_name));
  ui->label_name->setText(QString::fromStdString(subject_name));
}

ValueInputDialog::~ValueInputDialog() { delete ui; }

void ValueInputDialog::on_pushButton_accept_clicked() {
  *_ret_value = ui->lineEdit->text().toInt();
  accept();
}

void ValueInputDialog::on_pushButton_finish_clicked() {
  *_ret_value = -1;
  accept();
}
