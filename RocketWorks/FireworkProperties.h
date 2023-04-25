#include <QObject>
#include <QColor>
#include <QPoint>
#include "FireworkShapeEnum.h"
#ifndef FIREWORKPROPERTIES_H
#define FIREWORKPROPERTIES_H

class FireworkProperties : public QObject
{
    Q_OBJECT
public:
    explicit FireworkProperties();
    int getFlightDuration();
    int getBlastStrength();
    int getShellDiameter();
    QColor getParticleColor();
    QString getSound();
    QPoint getBlastCenter();
    void setBlastCenter(QPoint blastCenter);
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
    QPoint blastCenter;
};

#endif // FIREWORKPROPERTIES_H
