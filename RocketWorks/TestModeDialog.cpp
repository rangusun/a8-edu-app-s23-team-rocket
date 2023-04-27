#include "TestModeDialog.h"
#include "ui_TestModeDialog.h"
#include <QPainter>

TestModeDialog::TestModeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestModeDialog)
{
    ui->setupUi(this);

    connect(ui->sandboxButton,
            &QPushButton::clicked,
            this,
            &TestModeDialog::switchToSandbox);
    connect(ui->buttonBox,
            &QDialogButtonBox::clicked,
            this,
            &TestModeDialog::enableButtons);

    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint );

}

void TestModeDialog::displaySpecificationsDialog(QString shapeSpec, QString colorSpec, QString soundSpec, int shellDiameterSpec)
{
    ui->specificationsLabel->setText("Please build a " + colorSpec +
                                     " firework whose shell is " + QString::number(shellDiameterSpec) +
                                     " inches in diameter. I want the firework to explode in the shape of a " + shapeSpec +
                                     " and make a " + soundSpec + " sound.");
    show();
}

TestModeDialog::~TestModeDialog()
{
    delete ui;
}

void TestModeDialog::switchToSandbox()
{
    close();
    emit changeToSandbox();
}

void TestModeDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QRect orderGeometry = ui->orderLayout->geometry();

    QImage orderSheet(":/TestModeResources/Resources/orderForm.png");

    painter.drawImage(orderGeometry, orderSheet);
}
