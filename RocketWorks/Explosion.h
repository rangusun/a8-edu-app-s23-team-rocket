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

    void explodeCircle(int numParticles, int impulseStrength, int yOffset);
    void explodeLineBetweenPoints(QPoint point1, QPoint point2, int numParticles, int impulseStrength,
                                  int yOffset, double xRandVariance, double yRandVariance, int &particleNum);
    void explodeHeart(int numParticles, int impulseStrength, int yOffset);
    void explodeStar(int numParticles, int impulseStrength, int yOffset);
    void explodeSmiley(int numParticles, int impulseStrength, int yOffset);
};

#endif // EXPLOSION_H
