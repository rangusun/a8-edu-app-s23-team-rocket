#include "Explosion.h"

Explosion::Explosion(FireworkProperties *fireworkProps, B2DWorldWrapper *world, QObject *parent)
    : QObject{parent},
    fireworkProps(fireworkProps),
    world(world)
{
    impulseStrength = fireworkProps->getBlastStrength();
    numParticles = impulseStrength * 15 - 24;

    blastCenterY = world->getObject("shell").cartY + 20;

    switch(fireworkProps->getShape())
    {
        case(circle):
            explodeCircle();
            break;

        case(heart):
            explodeHeart();
            break;

        case(star):
            explodeStar();
            break;

        case(smile):
            explodeSmiley();
            break;

        default:
            explodeCircle();
            break;
    }
}

void Explosion::explodeCircle()
{
    const double angleIncrement = (2*3.14159265358979323846) / numParticles;

    for (int i = 0; i < numParticles; i++)
    {
            //"firework" is the position we want to spawn all particles from.
            double jitterX = (rand() % (impulseStrength)) / 3;
            double jitterY = (rand() % (impulseStrength)) / 3;

            double cosine = cos(i*angleIncrement);
            double sine = sin(i*angleIncrement);

            world->addObject(WorldObject::makeWorldObjectFromCartCoords("particle"+std::to_string(i), cosine * (fireworkProps->getBlastStrength() * 0.6),
                                                                        sine * (fireworkProps->getBlastStrength() * 0.6) + blastCenterY, 1, 1));

            int x = (int)(impulseStrength * (cos(i * angleIncrement))) + jitterX;
            int y = (int)(impulseStrength * (sin(i * angleIncrement))) + jitterY;
            world->applyForceToObject("particle"+std::to_string(i), 0, 20);
            world->applyForceToObject("particle"+std::to_string(i), x, y);
    }
}

void Explosion::explodeLineBetweenPoints(QPoint point1, QPoint point2, int numParticles, int impulseStrength, double xRandVariance, double yRandVariance, int &particleNum)
{
    QPoint leftPoint = point1.x() < point2.x() ? point1 : point2;
    QPoint rightPoint = point1.x() < point2.x() ? point2 : point1;

    float dx = rightPoint.x() - leftPoint.x();
    float dy = rightPoint.y() - leftPoint.y();

    float distance = qSqrt(dx * dx + dy * dy);
    float increment = distance/numParticles;

    float slope = dy / dx;

    float xIncrement = qSqrt(increment*increment / (1.0 + slope*slope));
    float yIncrement = slope * xIncrement;

    for (int i = 0; i < numParticles; i++)
    {
            float xPosJitter = (rand() % (impulseStrength))/xRandVariance;
            float yForceJitter = (rand() % (impulseStrength))/yRandVariance;
            float yPosJitter = (rand() % (impulseStrength))/yRandVariance;

            int x = leftPoint.x() + (i * xIncrement) + xPosJitter;
            int y = leftPoint.y() + (i * yIncrement) + yPosJitter;

            world->addObject(WorldObject::makeWorldObjectFromCartCoords("particle"+std::to_string(particleNum), x, y, 1, 1));

            // Caclulate force for particle
            int yDistFromCenter = y - blastCenterY;

            int forceY = yDistFromCenter + yForceJitter;

            world->applyForceToObject("particle"+std::to_string(particleNum), 0, 20);
            world->applyForceToObject("particle"+std::to_string(particleNum), x, forceY);

            particleNum++;
    }
}

void Explosion::explodeHeart()
{
    const double angleIncrement = (2*3.14159265358979323846) / numParticles;
    int particleNum = 0;

    // Draw top left of heart
    int offset = impulseStrength * 0.6;

    for (int i = numParticles * 0.1; i < numParticles * 0.6; i++)
    {
            //"firework" is the position we want to spawn all particles from.
            double jitterY = (rand() % (impulseStrength)) / 3;

            double cosine = cos(i * angleIncrement);
            double sine = sin(i * angleIncrement);

            int x = cosine * (offset) - offset;
            int y = sine * (offset) + blastCenterY;

            world->addObject(WorldObject::makeWorldObjectFromCartCoords("particle"+std::to_string(particleNum), x, y, 1, 1));

            int forceY = (int)((offset) * (sin(i * angleIncrement))) + jitterY;

            world->applyForceToObject("particle"+std::to_string(particleNum), 0, 20);
            world->applyForceToObject("particle"+std::to_string(particleNum), x, forceY);

            particleNum++;
    }

    // Draw top right of heart
    for (int i = numParticles * -0.1; i < numParticles * 0.5; i++)
    {
            //"firework" is the position we want to spawn all particles from.
            double jitterY = (rand() % (impulseStrength)) / 3;

            double cosine = cos(i * angleIncrement);
            double sine = sin(i * angleIncrement);

            int x = cosine * (offset) + offset;
            int y = sine * (offset) + blastCenterY;

            world->addObject(WorldObject::makeWorldObjectFromCartCoords("particle"+std::to_string(particleNum), x, y, 1, 1));

            int forceY = (int)((offset) * (sin(i * angleIncrement))) + jitterY;

            world->applyForceToObject("particle"+std::to_string(particleNum), 0, 20);
            world->applyForceToObject("particle"+std::to_string(particleNum), x, forceY);

            particleNum++;
    }

    // Draw top left of heart
    QPoint topLeft(-offset * 2 - 1, blastCenterY - 2);
    QPoint bottom(0, blastCenterY - (impulseStrength * 1.3));

    explodeLineBetweenPoints(topLeft, bottom, numParticles/2.0, impulseStrength, 5.0, 10.0, particleNum);

    // Draw bottom right of heart
    QPoint topRight(offset * 2 - 1, blastCenterY - 2);
    explodeLineBetweenPoints(bottom, topRight, numParticles/2.0, impulseStrength, 5.0, 10.0, particleNum);
}

void Explosion::explodeStar()
{
    numParticles = impulseStrength * 13;

    // Calculate star's outer points
    QVector<QPoint> outerPoints;
    for (int i = 0; i < 5; i++)
    {
            double angle = 2 * M_PI * i / 5.0 + M_PI * 0.5;
            float x = impulseStrength * cos(angle);
            float y = impulseStrength * sin(angle) + blastCenterY;
            outerPoints.push_back(QPoint(x, y));
    }

    // Calculate star's inner points
    QVector<QPoint> innerPoints;
    for (int i = 0; i < 5; i++)
    {
            double angle = 2 * M_PI * i / 5.0 + M_PI * 1.5;
            float x = (impulseStrength/3.0) * (cos(angle) + 3.0/impulseStrength);
            float y = (impulseStrength/3.0) * (sin(angle) + 3.0/impulseStrength) + blastCenterY;
            innerPoints.push_back(QPoint(x, y));
    }

    int particleNum = 0;

    // Connect points with lines
    for (int i = 0; i < 5; i++)
    {
            explodeLineBetweenPoints(outerPoints[i], innerPoints[(i + 3) % innerPoints.size()], numParticles/5.0,
                                     impulseStrength + 3/impulseStrength, 10.0, 10.0, particleNum);
            explodeLineBetweenPoints(outerPoints[i], innerPoints[(i + 2) % innerPoints.size()], numParticles/5.0,
                                     impulseStrength + 3/impulseStrength, 10.0, 10.0, particleNum);
    }
}

void Explosion::explodeSmiley()
{
    const double angleIncrement = (2*3.14159265358979323846) / numParticles;
    int particleNum = 0;

    // Mouth of smiley
    for (int i = numParticles/2.0; i < numParticles; i++)
    {
            //"firework" is the position we want to spawn all particles from.
            double jitterX = (rand() % (impulseStrength)) / 3;
            double jitterY = (rand() % (impulseStrength)) / 3;

            double cosine = cos(i*angleIncrement);
            double sine = sin(i*angleIncrement);

            world->addObject(WorldObject::makeWorldObjectFromCartCoords("particle"+std::to_string(particleNum), cosine * (fireworkProps->getBlastStrength() * 0.6),
                                                                       sine * (fireworkProps->getBlastStrength() * 0.6) + blastCenterY, 1, 1));

            int x = (int)(impulseStrength * (cos(i * angleIncrement))) + jitterX;
            int y = (int)(impulseStrength * (sin(i * angleIncrement))) + jitterY;

            world->applyForceToObject("particle"+std::to_string(particleNum), 0, 20);
            world->applyForceToObject("particle"+std::to_string(particleNum), x, y);

            particleNum++;
    }

    // Left Eye
    for (int i = 0; i < numParticles/4.0; i++)
    {
            //"firework" is the position we want to spawn all particles from.
            double jitterX = (rand() % (impulseStrength)) / 5;
            double yForceJitter = (rand() % (impulseStrength)) / 3;
            double yPosJitter = (rand() % (impulseStrength)) / 3;

            int x = (int)(impulseStrength * -0.4) + jitterX;
            int y = (int)(impulseStrength * i * 0.03) + yPosJitter + blastCenterY;

            world->addObject(WorldObject::makeWorldObjectFromCartCoords("particle"+std::to_string(particleNum), x, y, 1, 1));

            int forceY = (int)(impulseStrength * i * 0.03) + yForceJitter;

            world->applyForceToObject("particle"+std::to_string(particleNum), 0, 20);
            world->applyForceToObject("particle"+std::to_string(particleNum), x, forceY);

            particleNum++;
    }

    // Right Eye
    for (int i = 0; i < numParticles/4.0; i++)
    {
            //"firework" is the position we want to spawn all particles from.
            double jitterX = (rand() % (impulseStrength)) / 5;
            double yForceJitter = (rand() % (impulseStrength)) / 3;
            double yPosJitter = (rand() % (impulseStrength)) / 3;

            int x = (int)(impulseStrength * 0.4) + jitterX;
            int y = (int)(impulseStrength * i * 0.03) + yPosJitter + blastCenterY;

            world->addObject(WorldObject::makeWorldObjectFromCartCoords("particle"+std::to_string(particleNum), x, y, 1, 1));

            int forceY = (int)(impulseStrength * i * 0.03) + yForceJitter;

            world->applyForceToObject("particle"+std::to_string(particleNum), 0, 20);
            world->applyForceToObject("particle"+std::to_string(particleNum), x, forceY);

            particleNum++;
    }
}
