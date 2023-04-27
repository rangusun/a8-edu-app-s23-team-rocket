#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "FireworkProperties.h"
#include "B2DWorldWrapper.h"
#include <QObject>

class Explosion : public QObject
{
    Q_OBJECT
public:
    explicit Explosion(FireworkProperties *fireworkProps, B2DWorldWrapper *world,  QObject *parent = nullptr);

signals:

private:
    FireworkProperties *fireworkProps;
    B2DWorldWrapper *world;

    int numParticles;
    int impulseStrength;
    int blastCenterY;

    void explodeCircle();
    void explodeLineBetweenPoints(QPoint point1, QPoint point2, int numParticles, int impulseStrength, double xRandVariance, double yRandVariance, int &particleNum);
    void explodeHeart();
    void explodeStar();
    void explodeSmiley();
};

#endif // EXPLOSION_H
