#include "TutorialPage.h"
#include "ui_TutorialPage.h"
#include <QPushButton>

TutorialPage::TutorialPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TutorialPage)
{
    ui->setupUi(this);

    dialogsVisited[stars] = false;
    dialogsVisited[blastCharge] = false;
    dialogsVisited[liftCharge] = false;
    dialogsVisited[other] = false;

    connect(ui->starButton,
            &QPushButton::clicked,
            this,
            [this]() { componentDialog.showComponentDialog(stars); dialogsVisited[stars] = true; CheckIfAllPagesVisited(); });
    connect(ui->blastButton,
            &QPushButton::clicked,
            this,
            [this]() { componentDialog.showComponentDialog(blastCharge); dialogsVisited[blastCharge] = true; CheckIfAllPagesVisited(); });
    connect(ui->liftButton,
            &QPushButton::clicked,
            this,
            [this]() { componentDialog.showComponentDialog(liftCharge); dialogsVisited[liftCharge] = true; CheckIfAllPagesVisited(); });
    connect(ui->otherButton,
            &QPushButton::clicked,
            this,
            [this]() { componentDialog.showComponentDialog(other); dialogsVisited[other] = true; CheckIfAllPagesVisited(); });

    connect(ui->nextButton,
            &QPushButton::clicked,
            this,
            &TutorialPage::switchToSandbox);
}

TutorialPage::~TutorialPage()
{
    delete ui;
}

void TutorialPage::CheckIfAllPagesVisited()
{
    for (const auto & [key, thisDialogVisited] : dialogsVisited)
    {
        if (!thisDialogVisited)
        {
            return;
        }
    }

    ui->nextButton->setEnabled(true);
}

void TutorialPage::switchToSandbox()
{
    emit changePage();
}
