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

    connect(ui->resetButton,
            &QPushButton::clicked,
            ui->fireworkScene,
            &FireworkSceneWidget::resetWorld);

    connect(ui->nightModeCheckBox,
            &QCheckBox::stateChanged,
            this,
            &FireworkSandbox::changeBackground);
}

FireworkSandbox::~FireworkSandbox()
{
    delete ui;
}

void FireworkSandbox::changeBackground(int checked)
{
    if (checked)
    {
        ui->fireworkScene->changeBackground(":/FireworkResources/Resources/nightBackground.png");
    }
    else
    {
        ui->fireworkScene->changeBackground(":/FireworkResources/Resources/paperBackground.png");
    }
}
