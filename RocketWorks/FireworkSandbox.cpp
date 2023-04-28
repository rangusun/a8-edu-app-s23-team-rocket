/**
 *  A8: Educational-App
 *
 *  @brief UI for building and displaying a firework.
 *
 *  By Anna Madsen, Carlos Gonzalez, Carter Edginton, Rachel Nguyen, and Zander Ruiz
 *  for CS 3505 in Spring 2023
*/
#include "FireworkSandbox.h"
#include "ui_FireworkSandbox.h"
#include <QPainter>

FireworkSandbox::FireworkSandbox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FireworkSandbox),
    controlPanelBackground(":/SandboxUIResources/Resources/caution-stripe-background.jpg")
{
    ui->setupUi(this);

    // Set up fireworks scene widget ------------------------------------
    connect(ui->launchButton,
            &QPushButton::clicked,
            ui->fireworkScene,
            &FireworkSceneWidget::launchRocket);

    connect(ui->nightModeCheckBox,
            &QCheckBox::stateChanged,
            this,
            &FireworkSandbox::changeBackground);

    connect(ui->shellDiameterSlider,
            &QSlider::valueChanged,
            &ui->fireworkScene->fireworkProps,
            &FireworkProperties::setShellDiameter);

    connect(ui->colorsDropdown,
            &QComboBox::currentTextChanged,
            &ui->fireworkScene->fireworkProps,
            &FireworkProperties::setColor);

    connect(ui->soundsDropdown,
            &QComboBox::currentTextChanged,
            &ui->fireworkScene->fireworkProps,
            &FireworkProperties::setSound);

    connect(ui->shapeDropdown,
            &QComboBox::currentTextChanged,
            &ui->fireworkScene->fireworkProps,
            &FireworkProperties::setShape);

    ui->fireworkScene->fireworkProps.setShellDiameter(ui->shellDiameterSlider->value());

    // Set up buttons to disable after firework is launched ---------------
    connect(ui->launchButton,
            &QPushButton::clicked,
            this,
            &FireworkSandbox::disableButtons);

    connect(ui->fireworkScene,
            &FireworkSceneWidget::enableButtons,
            this,
            &FireworkSandbox::enableButtons);

    connect(ui->launchButton,
            &QPushButton::clicked,
            this,
            [this]() { emit launch(ui->fireworkScene->fireworkProps); });

    // Set up shell preview ------------------------------------------------
    ui->shellPreview->setFireworkProperties(&ui->fireworkScene->fireworkProps);

    ui->shellPreview->update();

    connect(ui->shellDiameterSlider,
            &QSlider::valueChanged,
            this,
            [this]() { ui->shellPreview->update(); });
    connect(ui->shellDiameterSlider,
            &QSlider::valueChanged,
            this,
            [this](int value) {ui->diameterLabel->setText(QString::number(value) + " inches");});
    connect(ui->colorsDropdown,
            &QComboBox::currentTextChanged,
            this,
            [this]() { ui->shellPreview->update(); });
    connect(ui->shapeDropdown,
            &QComboBox::currentTextChanged,
            this,
            [this]() { ui->shellPreview->update(); });

    update();
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

void FireworkSandbox::disableButtons()
{
    ui->shellDiameterSlider->setEnabled(false);
    ui->colorsDropdown->setEnabled(false);
    ui->soundsDropdown->setEnabled(false);
    ui->shapeDropdown->setEnabled(false);
    ui->launchButton->setEnabled(false);
}

void FireworkSandbox::enableButtons()
{
    ui->shellDiameterSlider->setEnabled(true);
    ui->colorsDropdown->setEnabled(true);
    ui->soundsDropdown->setEnabled(true);
    ui->shapeDropdown->setEnabled(true);
    ui->launchButton->setEnabled(true);
}

void FireworkSandbox::switchModes(QString mode)
{
    if (mode == "test")
    {
        ui->shellPreview->showStarColor = false;
        ui->fireworkScene->testMode = true;

        // Changes dropdown sounds to thier test version
        ui->soundsDropdown->setItemText(0, "Bismuth");
        ui->soundsDropdown->setItemText(1, "Organic Compounds");
        ui->soundsDropdown->setItemText(2, "Gun Powder");
    }
    else
    {
        ui->shellPreview->showStarColor = true;
        ui->fireworkScene->testMode = false;
    }
}

