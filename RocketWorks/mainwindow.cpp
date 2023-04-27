#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->windowStack->addWidget(&tutorialPage);
    ui->windowStack->addWidget(&sandboxPage);
    ui->windowStack->addWidget(&testPage);
    ui->windowStack->setCurrentWidget(&tutorialPage);

    this->setFixedSize(tutorialPage.width() + 20, tutorialPage.height() + 50);

    connect(&tutorialPage,
            &TutorialPage::changePage,
            this,
            &MainWindow::switchToSandboxPage);
    connect(&sandboxPage,
            &FireworkSandboxMode::changeToTestmode,
            this,
            &MainWindow::switchToTestModePage);
    connect(&testPage,
            &FireworkTestMode::changeToSandbox,
            this,
            &MainWindow::switchToSandboxPage);
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
