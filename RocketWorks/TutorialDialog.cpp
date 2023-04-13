#include "TutorialDialog.h"
#include "ui_TutorialDialog.h"

TutorialDialog::TutorialDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TutorialDialog)
{
    ui->setupUi(this);

}

TutorialDialog::~TutorialDialog()
{
    delete ui;
}
