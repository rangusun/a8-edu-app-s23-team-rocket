
#include "FireworkSim.h"
#include "ui_FireworkSim.h"


FireworkSim::FireworkSim(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FireworkSim)
{
    ui->setupUi(this);
}

FireworkSim::~FireworkSim()
{
    delete ui;
}


