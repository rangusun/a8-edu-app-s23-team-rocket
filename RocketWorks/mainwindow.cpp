#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->currentWindowHolder->addWidget(&tutorialPage);

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
    ui->currentWindowHolder->addWidget(&sandboxPage);
}
