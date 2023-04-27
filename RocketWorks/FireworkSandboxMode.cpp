#include "FireworkSandboxMode.h"
#include "ui_FireworkSandboxMode.h"

FireworkSandboxMode::FireworkSandboxMode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FireworkSandboxMode),
    visited(false)
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
