#include "FireworkTestMode.h"
#include "ui_FireworkTestMode.h"

FireworkTestMode::FireworkTestMode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FireworkTestMode)
{
    ui->setupUi(this);

    connect(ui->sandboxModeButton,
            &QPushButton::clicked,
            this,
            &FireworkTestMode::switchToSandbox);
    connect(&model,
            &TestModeModel::specificationsGenerated,
            &testModeDialog,
            &TestModeDialog::displaySpecificationsDialog);

    // Inform the Firework sandbox window to show the stars as grey in the shell preview
    ui->widget->switchModes("test");
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
