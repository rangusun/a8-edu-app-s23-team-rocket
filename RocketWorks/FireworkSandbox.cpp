#include "FireworkSandbox.h"
#include "ui_FireworkSandbox.h"

FireworkSandbox::FireworkSandbox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FireworkSandbox)
{
    ui->setupUi(this);

}

FireworkSandbox::~FireworkSandbox()
{
    delete ui;
}
