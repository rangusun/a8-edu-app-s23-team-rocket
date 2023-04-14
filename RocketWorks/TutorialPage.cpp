#include "TutorialPage.h"
#include "ui_TutorialPage.h"
#include <QPushButton>

TutorialPage::TutorialPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TutorialPage),
    starDialog(":/TutorialResources/Resources/tempGunpowder.png", "Temp text", "Gunpowder"),
    blastDialog(":/TutorialResources/Resources/tempGunpowder.png",
                "-  This is what gives the size of the firework display! \n"
                        "-   Blast charges are made out of black powder. They send "
                        "firework stars off flying when they are ignited by the time "
                        "delay fuse in a firework. The time delay fuse has to be made "
                        "to the right length and burn time so that the firework does "
                        "not ignite when it’s too close to the ground.",
                "Gunpowder"),
    liftDialog(":/TutorialResources/Resources/tempGunpowder.png", "Temp text", "Gunpowder"),
    otherDialog(":/TutorialResources/Resources/tempGunpowder.png", "Temp text", "Gunpowder")
{
    ui->setupUi(this);

    dialogVisited["Star"] = false;
    dialogVisited["Blast"] = false;
    dialogVisited["Lift"] = false;
    dialogVisited["Other"] = false;

    connect(ui->starButton,
            &QPushButton::clicked,
            this,
            [this]() { starDialog.show(); dialogVisited["Star"] = true; CheckIfAllPagesVisited(); });
    connect(ui->blastButton,
            &QPushButton::clicked,
            this,
            [this]() { blastDialog.show(); dialogVisited["Blast"] = true; CheckIfAllPagesVisited(); });
    connect(ui->liftButton,
            &QPushButton::clicked,
            this,
            [this]() { liftDialog.show(); dialogVisited["Lift"] = true; CheckIfAllPagesVisited(); });
    connect(ui->otherButton,
            &QPushButton::clicked,
            this,
            [this]() { otherDialog.show(); dialogVisited["Other"] = true; CheckIfAllPagesVisited(); });
}

TutorialPage::~TutorialPage()
{
    delete ui;
}

void TutorialPage::CheckIfAllPagesVisited()
{
    for (const auto & [key, value] : dialogVisited)
    {
        if (!value)
        {
            return;
        }
    }

    ui->nextButton->setEnabled(true);
}
