#ifndef FIREWORKSCENEWIDGET_H
#define FIREWORKSCENEWIDGET_H

#include <QWidget>
#include <Box2D/Box2D.h>
#include <QTimer>
#include "B2DWorldWrapper.h"
#include "FireworkProperties.h"
#include <QSoundEffect>

class FireworkSceneWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FireworkSceneWidget(QWidget *parent = nullptr);
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
    QSoundEffect woosh, whistle, bang, crackle;


    B2DWorldWrapper world;

protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent* event);
};


#endif // FIREWORKSCENEWIDGET_H
