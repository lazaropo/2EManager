#ifndef VALUEINPUTDIALOG_H
#define VALUEINPUTDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class ValueInputDialog;
}
QT_END_NAMESPACE

class ValueInputDialog : public QDialog {
  Q_OBJECT

 public:
  ValueInputDialog(int *ret_value, const std::string &invoker_name,
                   const std::string &reciever_name,
                   const std::string &subject_name, QWidget *parent = nullptr);
  ~ValueInputDialog();

 private slots:
  void on_pushButton_accept_clicked();

  void on_pushButton_finish_clicked();

 private:
  Ui::ValueInputDialog *ui;
  int *_ret_value;
};
#endif  // VALUEINPUTDIALOG_H
