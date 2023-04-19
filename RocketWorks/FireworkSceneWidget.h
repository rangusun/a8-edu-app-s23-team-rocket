#ifndef FIREWORKSCENEWIDGET_H
#define FIREWORKSCENEWIDGET_H

#include <QWidget>
#include <Box2D/Box2D.h>
#include <QTimer>

class FireworkSceneWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FireworkSceneWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
signals:

public slots:
    void updateWorld();
    void launchRocket();
    void resetWorld();
    void changeBackground(QString imagePath);

private:
    b2World world;
    b2Body* rocketBody;
    QTimer timer;
    QImage image;
    QImage background;
    bool rocketMoving = false;
    bool reset = false;
    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef rocketBodyDef;
    // Define another box shape for our dynamic body.
    b2PolygonShape rocketDynamicBox;
    // Define the dynamic body fixture.
    b2FixtureDef rocketFixtureDef;


};


#endif // FIREWORKSCENEWIDGET_H
