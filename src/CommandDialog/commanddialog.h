#ifndef COMMANDDIALOG_H
#define COMMANDDIALOG_H

#include <QDialog>

#include "../Model/Controller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CommandDialog; }
QT_END_NAMESPACE

class CommandDialog : public QDialog
{
    Q_OBJECT

public:
    CommandDialog(QWidget *parent = nullptr);
    ~CommandDialog();

private:
    Ui::CommandDialog *ui;
};
#endif // COMMANDDIALOG_H
