#ifndef EFFECTDIALOG_H
#define EFFECTDIALOG_H

#include <QDialog>

#include "../Model/Controller.h"


QT_BEGIN_NAMESPACE
namespace Ui { class EffectDialog; }
QT_END_NAMESPACE

class EffectDialog : public QDialog
{
    Q_OBJECT

public:
    EffectDialog(QWidget *parent = nullptr);
    ~EffectDialog();

//   signals:
//    void closed();

//       private slots:
//    void onDialogClosed() {
//        emit closed();
//    }

protected:
//    virtual void closeEvent(QCloseEvent *event) override {
//        emit onDialogClosed();
//        event->accept();
//    }

//    pf2e_manager::SimpleEffectBuilder* getData() const {
//        return _director->buildEffectByName(ui->comboBox_effect->currentText()->toStdString(),
//                                            ui->lineEdit_duration->text()->toInt(),
//                                            ui->lineEdit_value->text()->toInt());
//    }


private:
    Ui::EffectDialog *ui;

    pf2e_manager::SimpleEffectBuilder* _builder = new pf2e_manager::SimpleEffectBuilder();
    pf2e_manager::EffectDirector* _director = new pf2e_manager::EffectDirector(_builder);
};
#endif // EFFECTDIALOG_H
