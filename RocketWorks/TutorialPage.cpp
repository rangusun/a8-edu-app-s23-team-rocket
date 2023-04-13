#include "TutorialPage.h"
#include "ui_TutorialPage.h"

TutorialPage::TutorialPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TutorialPage)
{
    ui->setupUi(this);
}

TutorialPage::~TutorialPage()
{
    delete ui;
}
