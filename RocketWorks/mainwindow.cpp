/**
 *  A8: An-Educational-App
 *
 *  @brief This is the main window that holds all the pages of the application.
 *         It displays one page at a time and can switch between the pages.
 *
 *  By Anna Madsen, Carlos Gonzalez, Carter Edginton, Rachel Nguyen, and Zander Ruiz
 *  for CS 3505 in Spring 2023
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Add all pages to the window stack to switch between them to display a page.
    ui->windowStack->addWidget(&tutorialPage);
    ui->windowStack->addWidget(&sandboxPage);
    ui->windowStack->addWidget(&testPage);
    ui->windowStack->setCurrentWidget(&tutorialPage);

    this->setFixedSize(tutorialPage.width() + 20, tutorialPage.height() + 50);

    // Get a signal from TutorialPage to switch to SandboxPage -------------
    connect(&tutorialPage,
            &TutorialPage::changePage,
            this,
            &MainWindow::switchToSandboxPage);
    // Get a signal from SandboxPage to switch to TestModePage -------------
    connect(&sandboxPage,
            &FireworkSandboxMode::changeToTestmode,
            this,
            &MainWindow::switchToTestModePage);
    // Get a signal from TestModePage to switch to SandboxPage -------------
    connect(&testPage,
            &FireworkTestMode::changeToSandbox,
            this,
            &MainWindow::switchToSandboxPage);
    // When entering Test Mode, start generating rocket specifications -----
    connect(&sandboxPage,
            &FireworkSandboxMode::changeToTestmode,
            &testPage,
            &FireworkTestMode::startTestMode);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::switchToSandboxPage()
{
    ui->windowStack->setCurrentWidget(&sandboxPage);

    ui->windowStack->resize(sandboxPage.size());
    this->setFixedSize(827, 695);

    // Show a welcoming dialog to the Sandbox page if this is the first
    // time the user has visited it.
    if (!sandboxPage.visited)
    {
        sandboxPage.sandboxDialog.show();
        sandboxPage.visited = true;
    }
}

void MainWindow::switchToTestModePage()
{
    ui->windowStack->setCurrentWidget(&testPage);

    ui->windowStack->resize(testPage.size());
    this->setFixedSize(1107, 688);
}
