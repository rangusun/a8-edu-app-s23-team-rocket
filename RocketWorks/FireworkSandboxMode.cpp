/**
 *  A8: Educational-App
 *
 *  @brief UI wrapper containing a FireworkSandbox widget in "sandbox" mode.
 *
 *  Allows user to freely experiment with firework materials and settings to learn
 *  the different parts of a firework.
 *
 *  By Anna Madsen, Carlos Gonzalez, Carter Edginton, Rachel Nguyen, and Zander Ruiz
 *  for CS 3505 in Spring 2023
*/
#include "FireworkSandboxMode.h"
#include "ui_FireworkSandboxMode.h"

FireworkSandboxMode::FireworkSandboxMode(QWidget *parent) :
    QWidget(parent),
    visited(false),
    ui(new Ui::FireworkSandboxMode)
{
    ui->setupUi(this);

    connect(ui->testModeButton,
            &QPushButton::clicked,
            this,
            &FireworkSandboxMode::switchToTestmode);
}

FireworkSandboxMode::~FireworkSandboxMode()
{
    delete ui;
}

void FireworkSandboxMode::switchToTestmode()
{
    emit changeToTestmode();
}
