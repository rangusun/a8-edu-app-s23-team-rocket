#include "FireworkSceneWidget.h"
#include "WorldObject.h"
#include <QPainter>
#include <QDebug>


FireworkSceneWidget::FireworkSceneWidget(QWidget *parent) :
    QWidget(parent),
    timer(this),
    image(":/FireworkResources/Resources/Firework.png"),
    background(":/FireworkResources/Resources/nightBackground.png"),
    world()
{
    background = background.scaled(this->width(), this->height());

    woosh.setSource(QUrl::fromLocalFile(":/FireworkResources/Resources/wavwoosh.wav"));
    whistle.setSource(QUrl::fromLocalFile(":/FireworkResources/Resources/wavwhistle.wav"));
    bang.setSource(QUrl::fromLocalFile(":/FireworkResources/Resources/wavbang.wav"));
    crackle.setSource(QUrl::fromLocalFile(":/FireworkResources/Resources/wavcrackle.wav"));


    connect(&world,
            &B2DWorldWrapper::worldUpdated,
            this,
            [this]() { update(); });
}

void FireworkSceneWidget::paintEvent(QPaintEvent *)
{
    // Create a painter
    QPainter painter(this);

    // Draw background
    painter.drawImage(0, 0, background);

    for (auto const &pair: world.getAllObjects())
    {
        const WorldObject& obj = pair.second;
        if(obj.name.find("particle") != string::npos)
        {
            QColor fireWorkColor = fireworkProps.getParticleColor();

            int alpha = 255 * (float(particleFadeTimer.first)/float(particleFadeTimer.second));
            alpha = alpha < 0 ? 0 : alpha;

            fireWorkColor.setAlpha(alpha);
            painter.setPen(fireWorkColor);

            if (alpha <= 10)
            {
                world.removeObject(obj.name);
                emit enableButtons();
            }
        }
        else
        {
            painter.setPen(QColor(255, 0, 0));
        }

        painter.drawRect(QRect(obj.drawX, obj.drawY, obj.width, obj.height));
    }

    if (!(particleFadeTimer.first <= 0))
    {
        particleFadeTimer.first -= (particleFadeTimer.second / particleFadeTimer.first * 0.13 * fireworkProps.getShellDiameter());
    }

    painter.end();
}

void FireworkSceneWidget::launchRocket()
{
    //sound
    woosh.stop();
    whistle.stop();
    crackle.stop();
    bang.stop();
    if (fireworkProps.getSound() == QString("Whistle"))
    {
        whistle.play();
    }
    else
    {
        woosh.play();
    }
    //end sound
    int baseLaunchPower = 35;
    WorldObject ground = world.getObject("ground");
    double shellY = ground.cartY  + ground.height/2.0 + fireworkProps.getShellDiameter()/2.0;

    world.addObject(WorldObject::makeWorldObjectFromCartCoords("shell", 0, shellY, fireworkProps.getShellDiameter(), fireworkProps.getShellDiameter()));
    world.applyForceToObject("shell", 0, baseLaunchPower * fireworkProps.getShellDiameter() * fireworkProps.getShellDiameter());
    QTimer::singleShot(fireworkProps.getFlightDuration(), this, &FireworkSceneWidget::explode);
    //TODO:: ADD CORRECT LAUNCH SFX
}

void FireworkSceneWidget::changeBackground(QString imagePath)
{
    background = QImage(imagePath);
    background = background.scaled(this->width(), this->height());
    update();
}

void FireworkSceneWidget::explode()
{
    //sound effects
    woosh.stop();
    whistle.stop();
    crackle.stop();
    bang.stop();
    //A switch statement would probably be better, but they are not compatible with QString.
    if (fireworkProps.getSound() == QString("Crackle"))
    {
        crackle.play();
    }
    else
    {
        bang.play();
    }

    //end sound stuff
    const int impulseStrength = fireworkProps.getBlastStrength();
    const int numParticles = impulseStrength * 15 - 24;

    WorldObject shell = world.getObject("shell");
    int blastY = shell.cartY + 20;
    world.removeObject("shell");

    particleFadeTimer = std::pair<int, int>(fireworkProps.getShellDiameter() * 45, fireworkProps.getShellDiameter() * 45);
    fireworkProps.setBlastCenter(QPoint(width()/2, shell.pixelY));

    qDebug()<<blastY;

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

void FireworkSceneWidget::explodeCircle(int numParticles, int impulseStrength, int yOffset)
{
    const double angleIncrement = (2*3.14159265358979323846) / numParticles;

    for (int i = 0; i < numParticles; i++)
    {
        //"firework" is the position we want to spawn all particles from.
        double jitterX = (rand() % (fireworkProps.getBlastStrength())) / 3;
        double jitterY = (rand() % (fireworkProps.getBlastStrength())) / 3;

        double cosine = cos(i*angleIncrement);
        double sine = sin(i*angleIncrement);

        world.addObject(WorldObject::makeWorldObjectFromCartCoords("particle"+std::to_string(i), cosine * (fireworkProps.getBlastStrength() * 0.6),
                                                                   sine * (fireworkProps.getBlastStrength() * 0.6) + yOffset, 1, 1));

        int x = (int)(impulseStrength * (cos(i * angleIncrement))) + jitterX;
        int y = (int)(impulseStrength * (sin(i * angleIncrement))) + jitterY;
        world.applyForceToObject("particle"+std::to_string(i), 0, 20);

        world.applyForceToObject("particle"+std::to_string(i), x, y);
    }
}

void FireworkSceneWidget::explodeLineBetweenPoints(QPoint point1, QPoint point2, int numParticles, int impulseStrength,
                                                   int yOffset, double xRandVariance, double yRandVariance, int &particleNum)
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

        world.addObject(WorldObject::makeWorldObjectFromCartCoords("particle"+std::to_string(particleNum), x, y, 1, 1));

        // Caclulate force for particle
        int yDistFromCenter = y - yOffset;

        int forceY = yDistFromCenter + yForceJitter;

        world.applyForceToObject("particle"+std::to_string(particleNum), 0, 20);
        world.applyForceToObject("particle"+std::to_string(particleNum), x, forceY);

        particleNum++;
    }
}

void FireworkSceneWidget::explodeHeart(int numParticles, int impulseStrength, int yOffset)
{
    const double angleIncrement = (2*3.14159265358979323846) / numParticles;
    int particleNum = 0;

    // Draw top left of heart
    int offset = impulseStrength * 0.6;

    for (int i = numParticles * 0.1; i < numParticles * 0.6; i++)
    {
        //"firework" is the position we want to spawn all particles from.
        double jitterX = (rand() % (fireworkProps.getBlastStrength())) / 3;
        double jitterY = (rand() % (fireworkProps.getBlastStrength())) / 3;

        double cosine = cos(i * angleIncrement);
        double sine = sin(i * angleIncrement);

        int x = cosine * (offset) - offset;
        int y = sine * (offset) + yOffset;

        world.addObject(WorldObject::makeWorldObjectFromCartCoords("particle"+std::to_string(particleNum), x, y, 1, 1));

        int forceY = (int)((offset) * (sin(i * angleIncrement))) + jitterY;

        world.applyForceToObject("particle"+std::to_string(particleNum), 0, 20);
        world.applyForceToObject("particle"+std::to_string(particleNum), x, forceY);

        particleNum++;
    }

    // Draw top right of heart
    for (int i = numParticles * -0.1; i < numParticles * 0.5; i++)
    {
        //"firework" is the position we want to spawn all particles from.
        double jitterX = (rand() % (fireworkProps.getBlastStrength())) / 3;
        double jitterY = (rand() % (fireworkProps.getBlastStrength())) / 3;

        double cosine = cos(i * angleIncrement);
        double sine = sin(i * angleIncrement);

        int x = cosine * (offset) + offset;
        int y = sine * (offset) + yOffset;

        world.addObject(WorldObject::makeWorldObjectFromCartCoords("particle"+std::to_string(particleNum), x, y, 1, 1));

        int forceY = (int)((offset) * (sin(i * angleIncrement))) + jitterY;

        world.applyForceToObject("particle"+std::to_string(particleNum), 0, 20);
        world.applyForceToObject("particle"+std::to_string(particleNum), x, forceY);

        particleNum++;
    }

    // Draw top left of heart
    QPoint topLeft(-offset * 2 - 1, yOffset - 2);
    QPoint bottom(0, yOffset - (impulseStrength * 1.3));

    explodeLineBetweenPoints(topLeft, bottom, numParticles/2.0, impulseStrength, yOffset, 5.0, 10.0, particleNum);

    // Draw bottom right of heart
    QPoint topRight(offset * 2 - 1, yOffset - 2);
    explodeLineBetweenPoints(bottom, topRight, numParticles/2.0, impulseStrength, yOffset, 5.0, 10.0, particleNum);
}

void FireworkSceneWidget::explodeStar(int numParticles, int impulseStrength, int yOffset)
{
    numParticles = impulseStrength * 13;

    // Calculate star's outer points
    QVector<QPoint> outerPoints;
    for (int i = 0; i < 5; i++)
    {
        double angle = 2 * M_PI * i / 5.0 + M_PI * 0.5;
        float x = impulseStrength * cos(angle);
        float y = impulseStrength * sin(angle) + yOffset;
        outerPoints.push_back(QPoint(x, y));
    }

    // Calculate star's inner points
    QVector<QPoint> innerPoints;
    for (int i = 0; i < 5; i++)
    {
        double angle = 2 * M_PI * i / 5.0 + M_PI * 1.5;
        float x = (impulseStrength/3.0) * (cos(angle) + 3.0/impulseStrength);
        float y = (impulseStrength/3.0) * (sin(angle) + 3.0/impulseStrength) + yOffset;
        innerPoints.push_back(QPoint(x, y));
    }

    int particleNum = 0;

    // Connect points with lines
    for (int i = 0; i < 5; i++)
    {
        explodeLineBetweenPoints(outerPoints[i], innerPoints[(i + 3) % innerPoints.size()], numParticles/5.0,
                                 impulseStrength + 3/impulseStrength, yOffset, 10.0, 10.0, particleNum);
        explodeLineBetweenPoints(outerPoints[i], innerPoints[(i + 2) % innerPoints.size()], numParticles/5.0,
                                 impulseStrength + 3/impulseStrength, yOffset, 10.0, 10.0, particleNum);
    }
}

void FireworkSceneWidget::explodeSmiley(int numParticles, int impulseStrength, int yOffset)
{
    const double angleIncrement = (2*3.14159265358979323846) / numParticles;
    int particleNum = 0;

    // Mouth of smiley
    for (int i = numParticles/2.0; i < numParticles; i++)
    {
        //"firework" is the position we want to spawn all particles from.
        double jitterX = (rand() % (fireworkProps.getBlastStrength())) / 3;
        double jitterY = (rand() % (fireworkProps.getBlastStrength())) / 3;

        double cosine = cos(i*angleIncrement);
        double sine = sin(i*angleIncrement);

        world.addObject(WorldObject::makeWorldObjectFromCartCoords("particle"+std::to_string(particleNum), cosine * (fireworkProps.getBlastStrength() * 0.6),
                                                                   sine * (fireworkProps.getBlastStrength() * 0.6) + yOffset, 1, 1));

        int x = (int)(impulseStrength * (cos(i * angleIncrement))) + jitterX;
        int y = (int)(impulseStrength * (sin(i * angleIncrement))) + jitterY;

        world.applyForceToObject("particle"+std::to_string(particleNum), 0, 20);
        world.applyForceToObject("particle"+std::to_string(particleNum), x, y);

        particleNum++;
    }

    // Left Eye
    for (int i = 0; i < numParticles/4.0; i++)
    {
        //"firework" is the position we want to spawn all particles from.
        double jitterX = (rand() % (fireworkProps.getBlastStrength())) / 5;
        double yForceJitter = (rand() % (fireworkProps.getBlastStrength())) / 3;
        double yPosJitter = (rand() % (fireworkProps.getBlastStrength())) / 3;

        int x = (int)(impulseStrength * -0.4) + jitterX;
        int y = (int)(impulseStrength * i * 0.03) + yPosJitter + yOffset;

        world.addObject(WorldObject::makeWorldObjectFromCartCoords("particle"+std::to_string(particleNum), x, y, 1, 1));

        int forceY = (int)(impulseStrength * i * 0.03) + yForceJitter;

        world.applyForceToObject("particle"+std::to_string(particleNum), 0, 20);
        world.applyForceToObject("particle"+std::to_string(particleNum), x, forceY);

        particleNum++;
    }

    // Right Eye
    for (int i = 0; i < numParticles/4.0; i++)
    {
        //"firework" is the position we want to spawn all particles from.
        double jitterX = (rand() % (fireworkProps.getBlastStrength())) / 5;
        double yForceJitter = (rand() % (fireworkProps.getBlastStrength())) / 3;
        double yPosJitter = (rand() % (fireworkProps.getBlastStrength())) / 3;

        int x = (int)(impulseStrength * 0.4) + jitterX;
        int y = (int)(impulseStrength * i * 0.03) + yPosJitter + yOffset;

        world.addObject(WorldObject::makeWorldObjectFromCartCoords("particle"+std::to_string(particleNum), x, y, 1, 1));

        int forceY = (int)(impulseStrength * i * 0.03) + yForceJitter;

        world.applyForceToObject("particle"+std::to_string(particleNum), 0, 20);
        world.applyForceToObject("particle"+std::to_string(particleNum), x, forceY);

        particleNum++;
    }
}

void FireworkSceneWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    changeBackground(":/FireworkResources/Resources/nightBackground.png");

    world.initializeWorld(width(), height(), 12.0);

    //world.addObject(WorldObject::makeWorldObjectFromCartCoords("firework", 0, -width()/2, 20, 30));

    world.startWorldUpdates();
}
