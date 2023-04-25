#ifndef FIREWORKSCENEWIDGET_H
#define FIREWORKSCENEWIDGET_H

#include <QWidget>
#include <Box2D/Box2D.h>
#include <QTimer>
#include "B2DWorldWrapper.h"
#include "FireworkProperties.h"

class FireworkSceneWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FireworkSceneWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);

    FireworkProperties fireworkProps;

signals:
    void enableButtons();

public slots:
    void launchRocket();
    void changeBackground(QString imagePath);
    void explode();

private:
    QTimer timer;
    QImage image;
    QImage background;
    bool rocketMoving = false;
    bool reset = false;
    std::pair<int, int> particleFadeTimer;

    B2DWorldWrapper world;

protected:
    void resizeEvent(QResizeEvent* event);
};


#endif // FIREWORKSCENEWIDGET_H
