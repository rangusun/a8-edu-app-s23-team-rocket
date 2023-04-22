#include "FireworkSandbox.h"
#include "ui_FireworkSandbox.h"
#include <QDebug>

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

    connect(ui->shellDiameterSlider,
            &QSlider::valueChanged,
            &fireworkProps,
            &FireworkProperties::setShellDiameter);

    connect(ui->colorsDropdown,
            &QComboBox::currentTextChanged,
            &fireworkProps,
            &FireworkProperties::setColor);
    connect(ui->soundsDropdown,
            &QComboBox::currentTextChanged,
            &fireworkProps,
            &FireworkProperties::setSound);

    connect(ui->shapeDropdown,
            &QComboBox::currentTextChanged,
            &fireworkProps,
            &FireworkProperties::setShape);
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

