#include"FireworkSceneWidget.h"
#include <QPainter>
#include <QDebug>


FireworkSceneWidget::FireworkSceneWidget(QWidget *parent) : QWidget(parent),
    world(b2Vec2(0.0f, 10.0f)),
    timer(this),
    image(":/FireworkResources/Resources/Firework.png"),
    background(":/FireworkResources/Resources/paperBackground.png")
{
    background.scaled(this->width(), this->height());

    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, 20.0f);
    //groundBodyDef.type = b2_staticBody;

    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    // Define the ground box shape.
    b2PolygonShape groundBox;

    // The extents are the half-widths of the box.
    groundBox.SetAsBox(50.0f, 10.0f);

    // Add the ground fixture to the ground body.
    groundBody->CreateFixture(&groundBox, 0.0f);

    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 0.0f);

    body = world.CreateBody(&bodyDef);

    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;

    // Override the default friction.
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.9;
    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);
    printf("Init world\n");

    connect(&timer, &QTimer::timeout, this, &FireworkSceneWidget::updateWorld);
    timer.start(10);
}

void FireworkSceneWidget::paintEvent(QPaintEvent *) {
    // Create a painter
    QPainter painter(this);

    // Draw background
    painter.drawImage(0, 0, background);

    b2Vec2 position = body->GetPosition();
    float angle = body->GetAngle();

//    printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);

    painter.drawImage((int)(position.x*20), (int)(position.y*20), image);
    //painter.drawImage(200, 200, image);
//    qDebug() << image;
    painter.end();
   }

void FireworkSceneWidget::updateWorld() {
    // It is generally best to keep the time step and iterations fixed.
    if(rocketMoving)
    {
        body->ApplyForce(b2Vec2(0,-100), body->GetWorldCenter(), true);
    }
    world.Step(1.0/60.0, 6, 2);
    update();
}

void FireworkSceneWidget::launchRocket()
{
    rocketMoving = true;
}

void FireworkSceneWidget::changeBackground(QString imagePath)
{
    background = QImage(imagePath);
    background.scaled(this->width(), this->height());
}
