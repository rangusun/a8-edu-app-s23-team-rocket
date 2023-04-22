
#include "FireworkProperties.h"

FireworkProperties::FireworkProperties()
{}

int FireworkProperties::getFlightDuration()
{
    return shellDiameter; //TODO: Optimize flight duration based on blast strength
}

int FireworkProperties::getBlastStrength()
{
    return shellDiameter; //TODO: Tweak blast strength value so that it looks good onscreen
}


QColor FireworkProperties::getParticleColor()
{

}

QString FireworkProperties::getSound()
{

}
FireworkShape FireworkProperties::getShape()
{

}

void FireworkProperties::setShellDiameter(int diameter)
{

}

void FireworkProperties::setColor(QString color)
{
    switch(color)
    {
    case "Strontium Salts":
        particleColor = QColor::red;
        return;
    case "Calcium Salts":
        particleColor = QColor::fromRgb(255, 132, 0);
        return;
    case "Sodium Salts":
        particleColor = QColor::yellow;
        return;
    case "Barium Salts":
        particleColor = QColor::green;
        return;
    case "Copper Salts":
        particleColor = QColor::blue;
        return;
    case "Strontium + Copper Compounds":
        particleColor = QColor::fromRgb(170, 96, 219);
        return;
    case "Aluminum":
        particleColor = QColor::white;
        return;
    case "Lithium":
        particleColor = QColor::fromRgb(255, 135, 211);
        return;
    }


}

void FireworkProperties::setSound(QString sound)
{

}

void FireworkProperties::setShape(QString shape)
{

}


