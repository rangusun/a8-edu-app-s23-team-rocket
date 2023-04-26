#include "TestModeDialog.h"
#include "ui_TestModeDialog.h"

TestModeDialog::TestModeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestModeDialog)
{
    ui->setupUi(this);
}

void TestModeDialog::displaySpecificationsDialog(QString shapeSpec, QString colorSpec, QString soundSpec, int shellDiameterSpec)
{
    show();
}

TestModeDialog::~TestModeDialog()
{
    delete ui;
}
