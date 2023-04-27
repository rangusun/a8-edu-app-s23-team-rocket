#include "WinLoseDialog.h"
#include "ui_winlosedialog.h"

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

void WinLoseDialog::displayUserWinOrLoss(bool didUserWin)
{
    if(didUserWin)
    {
        ui->titleLabel->setText("Success!");
        ui->bodyLabel->setText("The client was very happy with their firework. You're on a roll!\n\nHit \"OK\" to try and fulfill another order, or \"Go back to Sandbox\" to go back to experimenting (this will end your win streak).");
    }
    else
    {
        ui->titleLabel->setText("Uh Oh!");
        ui->bodyLabel->setText("That wasn't the firework your client was expecting. Keep trying!\n\nHit \"OK\" to try and fulfill another order, or \"Go back to Sandbox\" to go back to experimenting.");
    }
    show();
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
