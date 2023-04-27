#include "FireworkSceneWidget.h"
#include "WorldObject.h"
#include "Explosion.h"
#include <QPainter>
#include <QDebug>


FireworkSceneWidget::FireworkSceneWidget(QWidget *parent) :
    QWidget(parent),
    testMode(false),
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

                if (!testMode)
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

    WorldObject shell = world.getObject("shell");

    particleFadeTimer = std::pair<int, int>(fireworkProps.getShellDiameter() * 45, fireworkProps.getShellDiameter() * 45);
    fireworkProps.setBlastCenter(QPoint(width()/2, shell.pixelY));

    Explosion explosion(&fireworkProps, &world);
    world.removeObject("shell");
}

void FireworkSceneWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    changeBackground(":/FireworkResources/Resources/nightBackground.png");

    world.initializeWorld(width(), height(), 12.0);

    //world.addObject(WorldObject::makeWorldObjectFromCartCoords("firework", 0, -width()/2, 20, 30));

    world.startWorldUpdates();
}
