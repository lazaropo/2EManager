#include "commanddialog.h"
#include "ui_commanddialog.h"

CommandDialog::CommandDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CommandDialog)
{
    ui->setupUi(this);
}

CommandDialog::~CommandDialog()
{
    delete ui;
}

