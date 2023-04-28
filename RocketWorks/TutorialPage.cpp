/**
 *  A8: Educational-App
 *
 *  @brief UI for teaching users about components of fireworks and what they do.
 *
 *  By Anna Madsen, Carlos Gonzalez, Carter Edginton, Rachel Nguyen, and Zander Ruiz
 *  for CS 3505 in Spring 2023
*/
#include "TutorialPage.h"
#include "ui_TutorialPage.h"

TutorialPage::TutorialPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TutorialPage)
{
    ui->setupUi(this);

    // Dialogs have not been visited by the user yet.
    dialogsVisited[stars] = false;
    dialogsVisited[blastCharge] = false;
    dialogsVisited[liftCharge] = false;
    dialogsVisited[other] = false;

    // Will set visited flags when component dialog boxex have been opened --------------------------------------------------
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

    // This button allows the user to go to the Sandbox page --------------------------------------------------
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
    // Check to see if all tutorial dialogs has been visited at least once.
    for (const auto & [key, thisDialogVisited] : dialogsVisited)
    {
        if (!thisDialogVisited)
        {
            return;
        }
    }

    // If all tutorial dialogs have been visited, allow the user to go to
    // the next page.
    ui->nextButton->setEnabled(true);
}

void TutorialPage::switchToSandbox()
{
    emit changePage();
}
