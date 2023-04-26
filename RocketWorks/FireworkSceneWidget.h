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

    void explodeCircle(int numParticles, int impulseStrength, int yOffset);
    void explodeLineBetweenPoints(QPoint point1, QPoint point2, int numParticles, int impulseStrength,
                                  int yOffset, double xRandVariance, double yRandVariance, int &particleNum);
    void explodeHeart(int numParticles, int impulseStrength, int yOffset);
    void explodeStar(int numParticles, int impulseStrength, int yOffset);
    void explodeSmiley(int numParticles, int impulseStrength, int yOffset);

protected:
    void resizeEvent(QResizeEvent* event);
};


#endif // FIREWORKSCENEWIDGET_H
