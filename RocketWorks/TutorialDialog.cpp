#include "TutorialDialog.h"
#include "ui_TutorialDialog.h"

TutorialDialog::TutorialDialog(QString imagePath, QString text, QString title, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TutorialDialog),
    image(imagePath),
    text(text),
    title(title)
{
    ui->setupUi(this);

    ui->titleLabel->setText(this->title);
    ui->imageBox->setPixmap(this->image);
    ui->textBox->setText(this->text);
}

TutorialDialog::~TutorialDialog()
{
    delete ui;
}
