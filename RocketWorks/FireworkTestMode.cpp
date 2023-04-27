#include "FireworkTestMode.h"
#include "ui_FireworkTestMode.h"
#include <QPainter>

FireworkTestMode::FireworkTestMode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FireworkTestMode),
    visited(false)
{
    ui->setupUi(this);

    connect(&model,
            &TestModeModel::specificationsGenerated,
            this,
            [this](QString shapeSpec, QString colorSpec, QString soundSpec, int shellDiameterSpec)
            { if (!visited) testModeDialog.displaySpecificationsDialog(shapeSpec, colorSpec, soundSpec, shellDiameterSpec); });
    connect(&model,
            &TestModeModel::specificationsGenerated,
            this,
            &FireworkTestMode::displaySpecificationsDialog);
    connect(&model,
            &TestModeModel::specificationsGenerated,
            this,
            [this]() { if (!visited) ui->testModeSandbox->disableButtons(); else ui->testModeSandbox->enableButtons(); });
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
            this,
            &FireworkTestMode::displayOrderCorrect);
    connect(&model,
            &TestModeModel::userWinOrLoss,
            ui->testModeSandbox,
            &FireworkSandbox::disableButtons);
    connect(ui->newOrderButton,
            &QPushButton::clicked,
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
            &FireworkTestMode::updateOrdersFulfilled);
    connect(this,
            &FireworkTestMode::changeToSandbox,
            &model,
            &TestModeModel::resetWinStreak);
    connect(&testModeDialog,
            &TestModeDialog::enableButtons,
            ui->testModeSandbox,
            &FireworkSandbox::enableButtons);
    connect(&testModeDialog,
            &TestModeDialog::enableButtons,
            this,
            [this]() { visited = true; });
    connect(ui->sandboxButton,
            &QPushButton::clicked,
            this,
            &FireworkTestMode::switchToSandbox);

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
    ui->newOrderButton->setEnabled(false);
}

void FireworkTestMode::displaySpecificationsDialog(QString shapeSpec, QString colorSpec, QString soundSpec, int shellDiameterSpec)
{
    ui->orderLabel->setText("Please build a " + colorSpec +
                                     " firework whose shell is " + QString::number(shellDiameterSpec) +
                                     " inches in diameter. I want the firework to explode in the shape of a " + shapeSpec.toLower() +
                                     " and make a " + soundSpec.toLower() + " sound.");
}

void FireworkTestMode::updateOrdersFulfilled(int ordersFulfilled)
{
    if (ordersFulfilled <= 3)
    {
        ui->winStreakLabel->setText("Orders Fulfilled: " + QString::number(ordersFulfilled) + "/3");
    }
}

void FireworkTestMode::displayOrderCorrect(bool orderCorrect)
{
    if (orderCorrect)
    {
        ui->orderResultWindow->setText("Great job! Try another order when you're ready.");
    }
    else
    {
        ui->orderResultWindow->setText("Uh oh! That wasn't what the customer ordered. "
                                       "Try another order!");
    }

    ui->newOrderButton->setEnabled(true);
}

void FireworkTestMode::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QRect orderGeometry = ui->orderLayout->geometry();

    QImage orderSheet(":/TestModeResources/Resources/orderForm.png");

    painter.drawImage(orderGeometry, orderSheet);
}

void FireworkTestMode::listSpecifications(QString shapeSpec, QString colorSpec, QString soundSpec, int shellDiameterSpec)
{
    QString color = colorSpec.left(1).toUpper() + colorSpec.mid(1);

    ui->colorSpecsLabel->setText("Color: " + color);
    ui->sizeSpecsLabel->setText("Shell diameter: " + QString::number(shellDiameterSpec));
    ui->shapeSpecsLabel->setText("Shape: " + shapeSpec);
    ui->soundSpecsLabel->setText("Sound: " + soundSpec);
}
