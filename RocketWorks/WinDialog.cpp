#include "WinDialog.h"
#include "ui_WinDialog.h"

WinLoseDialog::WinLoseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WinLoseDialog)
{
    ui->setupUi(this);
    connect(ui->sandBoxButton,
            &QPushButton::clicked,
            this,
            &WinLoseDialog::switchToSandbox);
    connect(ui->buttonBox,
            &QDialogButtonBox::clicked,
            this,
            &WinLoseDialog::newTest);
}

void WinLoseDialog::switchToSandbox()
{
    close();
    emit backToSandbox();
}

WinLoseDialog::~WinLoseDialog()
{
    delete ui;
}
