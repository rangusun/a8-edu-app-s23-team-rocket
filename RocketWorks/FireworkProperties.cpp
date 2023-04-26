#include "FireworkProperties.h"

FireworkProperties::FireworkProperties()
{
    shape = circle;
    shellDiameter = 3;
    particleColor = QColor("white");
    sound = "Crackle";
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

QPoint FireworkProperties::getBlastCenter()
{
    return blastCenter;
}

void FireworkProperties::setBlastCenter(QPoint blastCenter)
{
    this->blastCenter = blastCenter;
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
    if(color == "Strontium Salts" || color == "red")
    {
        particleColor = QColor("red");
    }
    else if(color == "Calcium Salts" || color == "orange")
    {
        // Orange
        particleColor = QColor::fromRgb(255, 132, 0);
    }
    else if(color == "Sodium Salts" || color == "yellow")
    {
        particleColor = QColor("yellow");
    }
    else if(color == "Barium Salts" || color == "green")
    {
        // Green
        particleColor = QColor::fromRgb(33, 255, 92);
    }
    else if(color == "Copper Salts" || color == "blue")
    {
        // Blue
        particleColor = QColor::fromRgb(7, 207, 224);
    }
    else if(color == "Strontium + Copper Compounds" || color == "purple")
    {
        // Purple
        particleColor = QColor::fromRgb(170, 96, 219);
    }
    else if(color == "Aluminum" || color == "white")
    {
        particleColor = QColor("white");
    }
    else if(color == "Lithium" || color == "pink")
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
    this->sound = sound;
}

void FireworkProperties::setShape(QString shapeString)
{
    if(shapeString == "Star")
        shape = star;
    else if (shapeString == "Heart")
        shape = heart;
    else if (shapeString == "Smile")
        shape = smile;
    else if (shapeString == "Circle")
        shape = circle;
    else
        shape = circle;
}


