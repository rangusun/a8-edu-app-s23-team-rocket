/**
 *  A8: An-Educational-App
 *
 *  @brief Popup dialog to inform the user about the sandbox mode.
 *
 *  By Anna Madsen, Carlos Gonzalez, Carter Edginton, Rachel Nguyen, and Zander Ruiz
 *  for CS 3505 in Spring 2023
*/
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
