#include "FireworkSandbox.h"
#include "ui_FireworkSandbox.h"

FireworkSandbox::FireworkSandbox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FireworkSandbox)
{
    ui->setupUi(this);

    connect(ui->launchButton,
            &QPushButton::clicked,
            ui->fireworkScene,
            &FireworkSceneWidget::launchRocket);
}

FireworkSandbox::~FireworkSandbox()
{
    delete ui;
}
