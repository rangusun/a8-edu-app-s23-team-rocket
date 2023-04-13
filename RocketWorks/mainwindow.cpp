#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget->show();



    connect(ui->launchButton,
            &QPushButton::clicked,
            ui->widget,
            &FireworkSceneWidget::launchRocket);
}

MainWindow::~MainWindow()
{
    delete ui;
}

