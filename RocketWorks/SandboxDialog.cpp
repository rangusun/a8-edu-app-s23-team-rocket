#include "SandboxDialog.h"
#include "ui_SandboxDialog.h"
#include <QPainter>

SandboxDialog::SandboxDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SandboxDialog)
{
    ui->setupUi(this);
}

SandboxDialog::~SandboxDialog()
{
    delete ui;
}
