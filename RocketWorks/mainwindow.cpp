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
    ui->windowStack->setCurrentWidget(&tutorialPage);

    qDebug() << "Tutorial Page Width" << tutorialPage.width() << "Tutorial Page Height" << tutorialPage.height();
    this->setFixedSize(tutorialPage.width() + 20, tutorialPage.height() + 50);

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
    qDebug() << "Sandbox Page Width" << sandboxPage.width() << "Sandbox Page Height" << sandboxPage.height();
    ui->windowStack->resize(sandboxPage.size());
    qDebug() << "Windowstack Width" << ui->windowStack->width() << "Windowstack Height" << ui->windowStack->height();
    this->setFixedSize(sandboxPage.width() + 2, sandboxPage.height() + 20);
    qDebug() << "Mainwindow Width" << width() << "Windowstack Height" << height();
}
