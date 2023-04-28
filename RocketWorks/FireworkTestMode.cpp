#include "FireworkTestMode.h"
#include "ui_FireworkTestMode.h"
#include <QPainter>

FireworkTestMode::FireworkTestMode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FireworkTestMode),
    visited(false)
{
    ui->setupUi(this);

    // Generate rocket specifications and display them for the user to see
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
    // Change to the Sandbox page when the user wants to ----------------
    connect(&testModeDialog,
            &TestModeDialog::changeToSandbox,
            this,
            &FireworkTestMode::switchToSandbox);
    // Check the user's rocket to see if specifications for the order is correct
    connect(ui->testModeSandbox,
            &FireworkSandbox::launch,
            &model,
            &TestModeModel::checkUserSelections);
    // Display how many orders the user correctly fulfilled--------------
    connect(&model,
            &TestModeModel::userWinOrLoss,
            this,
            &FireworkTestMode::displayOrderCorrect);
    // Enable the sandbox button once the user completes an order -------
    connect(&model,
            &TestModeModel::userWinOrLoss,
            this,
            [this]() { ui->sandboxButton->setEnabled(true); });
    // Generate new specifications when the user is taking another order-
    connect(ui->newOrderButton,
            &QPushButton::clicked,
            this,
            &FireworkTestMode::startTestMode);
    // Switch back to the Sandbox from the win dialog -------------------
    connect(&winDialog,
            &WinDialog::backToSandbox,
            this,
            &FireworkTestMode::switchToSandbox);
    // Display the specifications on the UI for the user to see ---------
    connect(&model,
            &TestModeModel::specificationsGenerated,
            this,
            &FireworkTestMode::listSpecifications);
    // Update the score of how many orders the user correctly fulfilled -
    connect(&model,
            &TestModeModel::winCountChanged,
            this,
            &FireworkTestMode::updateOrdersFulfilled);
    // Reset the score when the user goes back to the Sandbox -----------
    connect(this,
            &FireworkTestMode::changeToSandbox,
            &model,
            &TestModeModel::resetWinCount);
    // Disable the rocket configurations when a dialog box is up --------
    connect(&model,
            &TestModeModel::userWinOrLoss,
            ui->testModeSandbox,
            &FireworkSandbox::disableButtons);
    // Enable firework configuations when dialog boxes are closed -------
    connect(&testModeDialog,
            &TestModeDialog::enableButtons,
            ui->testModeSandbox,
            &FireworkSandbox::enableButtons);
    connect(&testModeDialog,
            &TestModeDialog::enableButtons,
            this,
            [this]() { visited = true; });
    // Switch back to Sandbox -------------------------------------------
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
    ui->sandboxButton->setEnabled(false);
    ui->orderResultWindow->setText("");
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

    if (ordersFulfilled == 3)
    {
        winDialog.show();
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
