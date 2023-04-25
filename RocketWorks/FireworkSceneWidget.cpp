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

    //qDebug() << "Ground width:" << ground.width << "Ground height:" << ground.height;
    //qDebug() << "Ground drawX:" << ground.drawX << "Ground drawY:" << ground.drawY;

    for (auto const &pair: world.getAllObjects())
    {
        const WorldObject& obj = pair.second;
        if(obj.name.find("particle") != string::npos)
        {
            painter.setPen(fireworkProps.getParticleColor());
        }
        else
        {
            painter.setPen(QColor(255, 0, 0));
        }

        painter.drawRect(QRect(obj.drawX, obj.drawY, obj.width, obj.height));
    }

    painter.end();
}

void FireworkSceneWidget::launchRocket()
{
    int baseLaunchPower = 35;
    WorldObject ground = world.getObject("ground");
    double shellY = ground.cartY  + ground.height/2.0 + fireworkProps.getShellDiameter()/2.0;

    world.addObject(WorldObject::makeWorldObjectFromCartCoords("shell", 0, shellY, fireworkProps.getShellDiameter(), fireworkProps.getShellDiameter()));
    world.applyForceToObject("shell", 0, baseLaunchPower * fireworkProps.getShellDiameter() * fireworkProps.getShellDiameter());
    QTimer::singleShot(fireworkProps.getFlightDuration(), this, &FireworkSceneWidget::explode);
}

void FireworkSceneWidget::resetWorld()
{
}

void FireworkSceneWidget::changeBackground(QString imagePath)
{
    background = QImage(imagePath);
    background = background.scaled(this->width(), this->height());
    update();
}

void FireworkSceneWidget::explode()
{
    qDebug()<<"boom!";
    const int numParticles = 150;
    const double angleIncrement = (2*3.14159265358979323846) / numParticles;
    const int impulseStrength = fireworkProps.getBlastStrength();

    int blastY = world.getObject("shell").cartY + 20;
    world.removeObject("shell");

    qDebug()<<blastY;


    for (int i = 0; i < numParticles; i++)
    {
        //"firework" is the position we want to spawn all particles from.
        double jitterX = (rand() % (fireworkProps.getBlastStrength())) / 3;
        double jitterY = (rand() % (fireworkProps.getBlastStrength())) / 3;


        double cosine = cos(i*angleIncrement);
        double sine = sin(i*angleIncrement);

        world.addObject(WorldObject::makeWorldObjectFromCartCoords("particle"+std::to_string(i), cosine * fireworkProps.getBlastStrength(), sine * fireworkProps.getBlastStrength() + blastY, 1, 1));

        int x = (int)(impulseStrength * (cos(i * angleIncrement))) + jitterX;
        int y = (int)(impulseStrength * (sin(i * angleIncrement))) + jitterY;
        world.applyForceToObject("particle"+std::to_string(i), 0, 20);

        world.applyForceToObject("particle"+std::to_string(i), x, y);

    }
}

void FireworkSceneWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    changeBackground(":/FireworkResources/Resources/nightBackground.png");

    world.initializeWorld(width(), height(), 10.0);

    //world.addObject(WorldObject::makeWorldObjectFromCartCoords("firework", 0, -width()/2, 20, 30));

    world.startWorldUpdates();
}
