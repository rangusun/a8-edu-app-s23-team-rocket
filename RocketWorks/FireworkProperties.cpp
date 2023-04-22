
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
    if(color == "Strontium Salts")
    {
        particleColor = QColor("red");
    }
    else if(color == "Calcium Salts")
    {
        particleColor = QColor::fromRgb(255, 132, 0);
    }
    else if(color == "Sodium Salts")
    {
        particleColor = QColor("yellow");
    }
    else if(color == "Barium Salts")
    {
        particleColor = QColor("green");
    }
    else if(color == "Copper Salts")
    {
        particleColor = QColor("blue");
    }
    else if(color == "Strontium + Copper Compounds")
    {
        particleColor = QColor::fromRgb(170, 96, 219);
    }
    else if(color == "Aluminum")
    {
        particleColor = QColor("white");
    }
    else if(color == "Lithium")
    {
        particleColor = QColor::fromRgb(255, 135, 211);
    }

}

void FireworkProperties::setSound(QString sound)
{

}

void FireworkProperties::setShape(QString shape)
{

}


