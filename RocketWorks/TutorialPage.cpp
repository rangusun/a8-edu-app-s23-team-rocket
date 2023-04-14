#include "TutorialPage.h"
#include "ui_TutorialPage.h"
#include <QPushButton>

TutorialPage::TutorialPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TutorialPage),
    gunpowderDialog(":/TutorialResources/Resources/tempGunpowder.png", "Temp text", "Gunpowder")
{
    ui->setupUi(this);

    connect(ui->gunpowderButton,
            &QPushButton::clicked,
            this,
            [this]() { gunpowderDialog.show(); dialogVisited["Gunpowder"] = true; });
}

TutorialPage::~TutorialPage()
{
    delete ui;
}
