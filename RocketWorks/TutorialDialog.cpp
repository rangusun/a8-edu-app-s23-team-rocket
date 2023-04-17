#include "TutorialDialog.h"
#include "ui_TutorialDialog.h"

TutorialDialog::TutorialDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TutorialDialog)
{
    ui->setupUi(this);
}

void TutorialDialog::showComponentDialog(RocketComponent component)
{
    ui->textBox->setMarkdown(getText(component));
    ui->titleLabel->setText(getTitle(component));
    ui->imageBox->setPixmap(getImage(component).scaled(250, 250, Qt::KeepAspectRatio));
    show();
}

QString TutorialDialog::getText(RocketComponent component)
{
    switch(component)
    {
    case star:
        return "This is what gives color to your fireworks!\n"
               "-  Stars are the most important component of a firework and the part you see in the night sky. They are small, flammable objects that get ignited and dispersed into the air by the blast charge when the firework shell is at a sufficient height.\n"
               "-  Stars can be made of a variety of metal salts and other chemical compounds to control color, sound, and light effects.\n"
               "-  Different Materials For Star Color:\n Strontium Salts: Creates red fireworks\n Calcium Salts: Creates orange fireworks\n Sodium Salts: Creates yellow fireworks\n Barium Salts: Creates green fireworks\n Copper Salts: Create blue fireworks\n Strontium + Copper Compounds: Creates purple fireworks\n Aluminum: Creates white fireworks\n"
               "-  Stars can be arranged in fun patterns inside the shell to create interesting firework shapes. These patterns are often created using cardboard, with stars glued along the outside.\n"
               "-  Star Components That Create Sounds:\n"
               "-  Bangs: Compacted, confined gun powder\n"
               "-  Crackling: Bismuth compounds divided in small granules\n"
               "-  Whistles: Aromatic organic compounds mixed with oxidiser\n";
    case liftCharge:
        return "-  This is what gives the size of the firework display!\n"
               "-  Blast charges are made out of black powder. They send firework stars off flying when they are ignited by the time delay fuse in a firework. The time delay fuse has to be made to the right length and burn time so that the firework does not ignite when it’s too close to the ground.";
    case blastCharge:
        return "-  This is what gives your fireworks height!/n"
               "-  Lift charges are placed in between the shell and the bottom of the launch tube of the firework which when ignited launches the firework upwards.\n"
               "-  Lift charges contain black powder, which is gun powder that is made with charcoal, sulfur, and potassium nitrate.\n"
               "-  Lift charges would not work without a launch tube - they rely on pressure buildup inside a closed space to propel the firework upward.\n"
               "-  The larger the lift charge is, the higher your firework will be launched!\n";
    case other:
        return "";
    }

    return "";
}

QString TutorialDialog::getTitle(RocketComponent component)
{
    switch(component)
    {
    case star:
        return "Firework Stars";
    case liftCharge:
        return "Lift Charge";
    case blastCharge:
        return "Blast Charge";
    case other:
        return "Other Components in an Aerial Firework";
    }
    return "";
}

QPixmap TutorialDialog::getImage(RocketComponent component)
{
    switch(component)
    {
    case star:
        return QPixmap(":/TutorialResources/Resources/tempStar.jpg");
    case liftCharge:
        return QPixmap(":/TutorialResources/Resources/tempGunpowder.png");
    case blastCharge:
        return QPixmap(":/TutorialResources/Resources/tempGunpowder.png");
    case other:
        return QPixmap(":/TutorialResources/Resources/tempShell.jpg");
    }
    QPixmap emptyPixmap;
    return emptyPixmap;
}

TutorialDialog::~TutorialDialog()
{
    delete ui;
}
