#include "EffectDialog.h"
#include "ui_effectdialog.h"

EffectDialog::EffectDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EffectDialog)
{
    ui->setupUi(this);
}

EffectDialog::~EffectDialog()
{
    delete ui;
}

