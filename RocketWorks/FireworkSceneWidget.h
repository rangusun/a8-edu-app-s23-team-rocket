#ifndef FIREWORKSCENEWIDGET_H
#define FIREWORKSCENEWIDGET_H

#include <QWidget>
#include <Box2D/Box2D.h>
#include <QTimer>
#include "B2DWorldWrapper.h"
#include "WorldObject.h"

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
    QTimer timer;
    QImage image;
    QImage background;
    bool rocketMoving = false;
    bool reset = false;

    B2DWorldWrapper world;

protected:
    void resizeEvent(QResizeEvent* event);
};


#endif // FIREWORKSCENEWIDGET_H
