/**
 *  A8: An-Educational-App
 *
 *  @brief Popup dialog to celebrate the user fulfilling 3 correct orders
 *
 *  By Anna Madsen, Carlos Gonzalez, Carter Edginton, Rachel Nguyen, and Zander Ruiz
 *  for CS 3505 in Spring 2023
*/
#include "WinDialog.h"
#include "ui_WinDialog.h"

WinDialog::WinDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WinDialog)
{
    ui->setupUi(this);
    connect(ui->sandBoxButton,
            &QPushButton::clicked,
            this,
            &WinDialog::switchToSandbox);
}

void WinDialog::switchToSandbox()
{
    close();
    emit backToSandbox();
}

WinDialog::~WinDialog()
{
    delete ui;
}
