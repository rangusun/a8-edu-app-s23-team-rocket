#include "FireworkTestMode.h"
#include "ui_FireworkTestMode.h"

FireworkTestMode::FireworkTestMode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FireworkTestMode)
{
    ui->setupUi(this);

    connect(&model,
            &TestModeModel::specificationsGenerated,
            &testModeDialog,
            &TestModeDialog::displaySpecificationsDialog);
    connect(&model,
            &TestModeModel::specificationsGenerated,
            ui->testModeSandbox,
            &FireworkSandbox::disableButtons);
    connect(&testModeDialog,
            &TestModeDialog::changeToSandbox,
            this,
            &FireworkTestMode::switchToSandbox);
    connect(ui->testModeSandbox,
            &FireworkSandbox::launch,
            &model,
            &TestModeModel::checkUserSelections);
    connect(&model,
            &TestModeModel::userWinOrLoss,
            &winLoseDialog,
            &WinLoseDialog::displayUserWinOrLoss);
    connect(&model,
            &TestModeModel::userWinOrLoss,
            ui->testModeSandbox,
            &FireworkSandbox::disableButtons);
    connect(&winLoseDialog,
            &WinLoseDialog::newTest,
            this,
            &FireworkTestMode::startTestMode);
    connect(&winLoseDialog,
            &WinLoseDialog::backToSandbox,
            this,
            &FireworkTestMode::switchToSandbox);
    connect(&model,
            &TestModeModel::specificationsGenerated,
            this,
            &FireworkTestMode::listSpecifications);
    connect(&model,
            &TestModeModel::winStreakChanged,
            this,
            [this](int streakCount){ui->winStreakLabel->setText("Win Streak: " + QString::number(streakCount));});
    connect(this,
            &FireworkTestMode::changeToSandbox,
            &model,
            &TestModeModel::resetWinStreak);
    connect(&testModeDialog,
            &TestModeDialog::enableButtons,
            ui->testModeSandbox,
            &FireworkSandbox::enableButtons);

    // Inform the Firework sandbox window to show the stars as grey in the shell preview
    ui->testModeSandbox->switchModes("test");
}

FireworkTestMode::~FireworkTestMode()
{
    delete ui;
}

void FireworkTestMode::switchToSandbox()
{
    emit changeToSandbox();
}

void FireworkTestMode::startTestMode()
{
    model.generateFireworkSpecifications();
}

void FireworkTestMode::listSpecifications(QString shapeSpec, QString colorSpec, QString soundSpec, int shellDiameterSpec)
{
    QString color = colorSpec.left(1).toUpper() + colorSpec.mid(1);

    ui->colorSpecsLabel->setText("Color: " + color);
    ui->sizeSpecsLabel->setText("Shell diameter: " + QString::number(shellDiameterSpec));
    ui->shapeSpecsLabel->setText("Shape: " + shapeSpec);
    ui->soundSpecsLabel->setText("Sound: " + soundSpec);
}
