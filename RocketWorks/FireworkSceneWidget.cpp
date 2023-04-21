#include "FireworkSceneWidget.h"
#include <QPainter>
#include <QDebug>


FireworkSceneWidget::FireworkSceneWidget(QWidget *parent) : QWidget(parent),
    timer(this),
    image(":/FireworkResources/Resources/Firework.png"),
    background(":/FireworkResources/Resources/paperBackground.png"),
    world()
{
    background.scaled(this->width(), this->height());

    connect(&world,
            &B2DWorldWrapper::worldUpdated,
            this,
            [this]() { update(); });

//    // Define the ground body.
//    b2BodyDef groundBodyDef;
//    groundBodyDef.position.Set(0.0f, 30.0f);
//    groundBodyDef.type = b2_staticBody;

//    // Call the body factory which allocates memory for the ground body
//    // from a pool and creates the ground box shape (also from a pool).
//    // The body is also added to the world.
//    b2Body* groundBody = world.CreateBody(&groundBodyDef);

//    // Define the ground box shape.
//    b2PolygonShape groundBox;

//    // The extents are the half-widths of the box.
//    groundBox.SetAsBox(50.0f, 10.0f);

//    // Add the ground fixture to the ground body.
//    groundBody->CreateFixture(&groundBox, 0.0f);

//    // Define the dynamic body. We set its position and call the body factory.
//    // b2BodyDef bodyDef;
//    rocketBodyDef.type = b2_dynamicBody;
//    rocketBodyDef.position.Set(10.0f, 30.0f);

//    rocketBody = world.CreateBody(&rocketBodyDef);

//    // Define another box shape for our dynamic body.

//    rocketDynamicBox.SetAsBox(1.0f, 1.0f);

//    // Define the dynamic body fixture.
//    rocketFixtureDef.shape = &rocketDynamicBox;

//    // Set the box density to be non-zero, so it will be dynamic.
//    rocketFixtureDef.density = 1.0f;

//    // Override the default friction.
//    rocketFixtureDef.friction = 0.3f;
//    rocketFixtureDef.restitution = 0.9;
//    // Add the shape to the body.
//    rocketBody->CreateFixture(&rocketFixtureDef);
//    printf("Init world\n");



//    connect(&timer, &QTimer::timeout, this, &FireworkSceneWidget::updateWorld);
//    timer.start(10);
}

void FireworkSceneWidget::paintEvent(QPaintEvent *)
{
    // Create a painter
    QPainter painter(this);

    // Draw background
    painter.drawImage(0, 0, background);

    WorldObject ground = world.getObject("ground");
    WorldObject firework = world.getObject("firework");

    painter.setPen(QColor(255, 0, 0));

    qDebug() << "Ground width:" << ground.width << "Ground height:" << ground.height;
    qDebug() << "Ground drawX:" << ground.drawX << "Ground drawY:" << ground.drawY;

    painter.drawRect(QRect(ground.drawX, ground.drawY, ground.width, ground.height));
    painter.drawRect(QRect(firework.drawX, firework.drawY, firework.width, firework.height));

    painter.end();
}

void FireworkSceneWidget::updateWorld() {
    // It is generally best to keep the time step and iterations fixed.
//    if(rocketMoving)
//    {
//        rocketBody->ApplyForce(b2Vec2(0,-100), rocketBody->GetWorldCenter(), true);
//        world.Step(1.0/60.0, 6, 2);
//        update();
//    }
}

void FireworkSceneWidget::launchRocket()
{
//    rocketMoving = true;
//    rocketBody->ApplyLinearImpulse(b2Vec2(0,-100), rocketBody->GetWorldCenter(), true);
}

void FireworkSceneWidget::resetWorld()
{
//   rocketMoving = false;
//    // Define the dynamic body. We set its position and call the body factory.
//   rocketBodyDef.type = b2_dynamicBody;
//   rocketBodyDef.position.Set(10.0f, 30.0f);

//   rocketBody = world.CreateBody(&rocketBodyDef);
//   rocketDynamicBox.SetAsBox(1.0f, 1.0f);
//   rocketFixtureDef.shape = &rocketDynamicBox;
//   // Set the box density to be non-zero, so it will be dynamic.
//   rocketFixtureDef.density = 1.0f;
//   // Override the default friction.
//   rocketFixtureDef.friction = 0.3f;
//   rocketFixtureDef.restitution = 0.9;
//   // Add the shape to the body.
//   rocketBody->CreateFixture(&rocketFixtureDef);
//   update();
//   //connect(&timer, &QTimer::timeout, this, &FireworkSceneWidget::updateWorld);
//  // timer.start(10);
}

void FireworkSceneWidget::changeBackground(QString imagePath)
{
    background = QImage(imagePath);
    background.scaled(this->width(), this->height());
    update();
}

void FireworkSceneWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    world.initializeWorld(width(), height(), 10.0);

    world.addObject(WorldObject::makeWorldObjectfromCartCoords("firework", 0, 0, 20, 30));

    world.startWorldUpdates();
}
