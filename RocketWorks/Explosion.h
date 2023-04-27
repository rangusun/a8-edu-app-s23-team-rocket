/**
 *  A8: Educational App
 *
 *  @brief Contains code/math for creating a particle explosion in the B2DWorld
 *
 *  An explosion is can be generated in the B2World by creating an Explosion object
 *  and giving a FireworksProperties object and B2DWorldWrapper. The explosion handles
 *  creating and placing particles at the right coordinates and giving them the appropriate
 *  vector of force to create an explosion in the world that matches the desired shape and
 *  size in the firework properties.
 *
 *  By Anna Madsen, Carlos Gonzalez, Carter Edginton, Rachel Nguyen, and Zander Ruiz
 *  for CS 3505 in Spring 2023
*/
#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "FireworkProperties.h"
#include "B2DWorldWrapper.h"
#include <QObject>

class Explosion : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief - Creates a new particle explosion in the world with the given firework properties.
     *
     * @param FireworkProperties *fireworkProps - The firework properties with which to create the explosion.
     * @param B2DWorldWrapper *world - The world in which to create the particle explosion.
     */
    explicit Explosion(FireworkProperties *fireworkProps, B2DWorldWrapper *world,  QObject *parent = nullptr);

signals:

private:
    FireworkProperties *fireworkProps;
    B2DWorldWrapper *world;

    int numParticles;
    int impulseStrength;
    int blastCenterY;

    /**
     * @brief - Helper method. Calculates the position and force to give each particle in the
     * world to create a circular explosion.
     */
    void explodeCircle();

    /**
     * @brief - Helper method. Positions particles at points along a line from one point to another and
     * calculates the force to have each particle eminate from the center of the blast.
     */
    void explodeLineBetweenPoints(QPoint point1, QPoint point2, int numParticles, int impulseStrength,
                                  double xRandVariance, double yRandVariance, int &particleNum);

    /**
     * @brief - Helper method. Calculates the position and force to give each particle in the
     * world to create a heart-shaped explosion.
     */
    void explodeHeart();

    /**
     * @brief - Helper method. Calculates the position and force to give each particle in the
     * world to create a star-shaped explosion.
     */
    void explodeStar();

    /**
     * @brief - Helper method. Calculates the position and force to give each particle in the
     * world to create a smiley-face-shaped explosion.
     */
    void explodeSmiley();
};

#endif // EXPLOSION_H
