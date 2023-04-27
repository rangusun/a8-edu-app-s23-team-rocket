#include "Explosion.h"

Explosion::Explosion(FireworkProperties *fireworkProps, B2DWorldWrapper *world, QObject *parent)
    : QObject{parent},
    fireworkProps(fireworkProps),
    world(world)
{
    const int impulseStrength = fireworkProps->getBlastStrength();
    const int numParticles = impulseStrength * 15 - 24;

    WorldObject shell = world->getObject("shell");
    int blastY = shell.cartY + 20;

    switch(fireworkProps.getShape())
    {
        case(circle):
            explodeCircle(numParticles, impulseStrength, blastY);
            break;

        case(heart):
            explodeHeart(numParticles, impulseStrength, blastY);
            break;

        case(star):
            explodeStar(numParticles, impulseStrength, blastY);
            break;

        case(smile):
            explodeSmiley(numParticles, impulseStrength, blastY);
            break;

        default:
            explodeCircle(numParticles, impulseStrength, blastY);
            break;
    }
}
