#include <QObject>
#include <QColor>
#include "FireworkShapeEnum.h"
#ifndef FIREWORKPROPERTIES_H
#define FIREWORKPROPERTIES_H

class FireworkProperties
{
public:
    FireworkProperties();
    int getFlightDuration();
    int getBlastStrength();
    QColor getParticleColor();
    QString getSound();
    FireworkShape getShape();

public slots:
    void setShellDiameter(int diameter);
    void setColor(QString color);
    void setSound(QString sound);
    void setShape(QString shape);
private:
    FireworkShape shape;
    int shellDiameter;
    QString sound;
    QColor particleColor;
};

#endif // FIREWORKPROPERTIES_H
