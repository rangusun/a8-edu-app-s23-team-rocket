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

private:
    b2World world;
    b2Body* body;
    QTimer timer;
    QImage image;
    bool rocketMoving = false;
};


#endif // FIREWORKSCENEWIDGET_H
