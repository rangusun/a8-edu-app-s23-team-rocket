#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->windowStack->addWidget(&tutorialPage);
    ui->windowStack->addWidget(&sandboxPage);
    ui->windowStack->setCurrentWidget(&tutorialPage);
    this->setFixedSize(tutorialPage.width(), tutorialPage.height() + 20);

    connect(&tutorialPage,
            &TutorialPage::changePage,
            this,
            &MainWindow::switchToSandboxPage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::switchToSandboxPage()
{
    ui->windowStack->setCurrentWidget(&sandboxPage);
    ui->windowStack->removeWidget(&tutorialPage);
    ui->windowStack->resize(sandboxPage.size());
    this->setFixedSize(sandboxPage.size());
}
