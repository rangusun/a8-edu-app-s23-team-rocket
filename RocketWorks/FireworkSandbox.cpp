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
            this,
            &FireworkSandbox::sliderValueChange);

    connect(ui->colorsDropdown,
            &QComboBox::currentTextChanged,
            this,
            &FireworkSandbox::colorDropdownChanged);
    connect(ui->soundsDropdown,
            &QComboBox::currentTextChanged,
            this,
            &FireworkSandbox::soundDropdownChanged);
    connect(ui->shapeDropdown,
            &QComboBox::currentTextChanged,
            this,
            &FireworkSandbox::shapeDropdownChanged);
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

void FireworkSandbox::sliderValueChange(int value)
{
    shellDiameter = value;
}

void FireworkSandbox::colorDropdownChanged(QString color)
{

}

void FireworkSandbox::soundDropdownChanged(QString sound)
{

}

void FireworkSandbox::shapeDropdownChanged(QString shape)
{

}
