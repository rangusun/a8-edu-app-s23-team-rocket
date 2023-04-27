/**
 *  A8: An-Educational-App
 *
 *  @brief This class stores all the properties for a firework object
 *   so it can be passed around to other classes.
 *
 *
 *  By
 *  for CS 3505 in Spring 2023
*/
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
    /**
     * @brief – Constructor that initializes a firework with some properties.
     *
     */
    explicit FireworkProperties();

    /**
     * @brief – Gets the flight duration of a firework
     *
     *
     * @return int – Flight duration time.
     */
    int getFlightDuration();

    /**
     * @brief – Gets the blast strength for the firework.
     *
     *
     * @return int – Blast strength.
     */
    int getBlastStrength();

    /**
     * @brief – Gets the shell diameter of the firework.
     *
     *
     * @return int – Shell Diameter.
     */
    int getShellDiameter();

    /**
     * @brief – Operator overloading that compares two FireworkProperties Objects.
     *
     *
     * @return bool – boolean value indicating whether the two objects are equal or not.
     */
    bool operator==(const FireworkProperties& other);

    /**
     * @brief – Operator overloading that compares two FireworkProperties Objects.
     *
     *
     * @return bool – boolean value indicating whether the two objects are equal or not.
     */
    bool operator!=(const FireworkProperties& other);

    /**
     * @brief – Getter for particle color.
     *
     *
     * @return QColor - The particle color.
     */
    QColor getParticleColor();

    /**
     * @brief – Getter for firework sound.
     *
     *
     * @return QString - The sound for the firework.
     */
    QString getSound();

    /**
     * @brief – Getter for blast center.
     *
     *
     * @return QPoint - The center of the blast.
     */
    QPoint getBlastCenter();

    /**
     * @brief – Setter for the blast center.
     *
     *
     * @param QPoint blastCenter - The center point for the blast.
     */
    void setBlastCenter(QPoint blastCenter);

    /**
     * @brief – Getter for firework shape.
     *
     *
     * @return FireworkShape - The shape of the firework.
     */
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
