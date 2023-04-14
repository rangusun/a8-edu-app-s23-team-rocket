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
    ui->titleLabel->setFixedHeight(20);
    ui->imageBox->setPixmap(this->image.scaled(250, 250, Qt::KeepAspectRatio));
    ui->textBox->setMarkdown(this->text);
}

TutorialDialog::~TutorialDialog()
{
    delete ui;
}
