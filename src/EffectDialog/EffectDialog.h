#ifndef EFFECTDIALOG_H
#define EFFECTDIALOG_H

#include <QDialog>

#include "../Model/Controller.h"
#include "DataSource.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class EffectDialog;
}
QT_END_NAMESPACE

class EffectDialog : public QDialog {
  Q_OBJECT

 public:
  EffectDialog(QWidget* parent = nullptr, DataSource* data = nullptr);
  ~EffectDialog();

 protected:
 private slots:
  void on_button_set_clicked();

 private:
  Ui::EffectDialog* ui;

  DataSource* _data;

  pf2e_manager::SimpleEffectBuilder* _builder =
      new pf2e_manager::SimpleEffectBuilder();
  pf2e_manager::EffectDirector* _director =
      new pf2e_manager::EffectDirector(_builder);
};
#endif  // EFFECTDIALOG_H
