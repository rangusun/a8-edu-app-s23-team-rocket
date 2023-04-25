#include "FireworkProperties.h"

FireworkProperties::FireworkProperties()
{
    shape = circle;
    shellDiameter = 3;
    particleColor = QColor("white");
    sound = "unimplemented";
}

int FireworkProperties::getFlightDuration()
{
    return shellDiameter * 50; //TODO: Optimize flight duration based on blast strength
}

int FireworkProperties::getBlastStrength()
{
    return shellDiameter; //TODO: Tweak blast strength value so that it looks good onscreen
}


QColor FireworkProperties::getParticleColor()
{
    return particleColor;
}

QString FireworkProperties::getSound()
{
    return sound;
}

FireworkShape FireworkProperties::getShape()
{
    return shape;
}

int FireworkProperties::getShellDiameter()
{
    return shellDiameter;
}

void FireworkProperties::setShellDiameter(int diameter)
{
    shellDiameter = diameter;
}

void FireworkProperties::setColor(QString color)
{
    if(color == "Strontium Salts")
    {
        particleColor = QColor("red");
    }
    else if(color == "Calcium Salts")
    {
        // Orange
        particleColor = QColor::fromRgb(255, 132, 0);
    }
    else if(color == "Sodium Salts")
    {
        particleColor = QColor("yellow");
    }
    else if(color == "Barium Salts")
    {
        // Green
        particleColor = QColor::fromRgb(33, 255, 92);
    }
    else if(color == "Copper Salts")
    {
        particleColor = QColor("blue");
    }
    else if(color == "Strontium + Copper Compounds")
    {
        // Purple
        particleColor = QColor::fromRgb(170, 96, 219);
    }
    else if(color == "Aluminum")
    {
        particleColor = QColor("white");
    }
    else if(color == "Lithium")
    {
        // Pink
        particleColor = QColor::fromRgb(255, 135, 211);
    }
    else
    {
        particleColor = QColor("white");
    }
}

void FireworkProperties::setSound(QString sound)
{
    sound = "unimplemented";
}

void FireworkProperties::setShape(QString shapeString)
{
    if(shapeString == "star")
        shape = star;
    else if (shapeString == "heart")
        shape = heart;
    else if (shapeString == "smile")
        shape = smile;
    else if (shapeString == "circle")
        shape = circle;
    else
        shape = circle;
}


