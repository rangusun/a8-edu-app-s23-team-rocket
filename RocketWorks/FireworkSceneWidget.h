/**
 *  A8: Educational-App
 *
 *  @brief Widget to display fireworks using Box2D physics.
 *
 *  By Anna Madsen, Carlos Gonzalez, Carter Edginton, Rachel Nguyen, and Zander Ruiz
 *  for CS 3505 in Spring 2023
*/
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
    /**
     * @brief – Creates a new FireworkSceneWidget
     */
    explicit FireworkSceneWidget(QWidget *parent = nullptr);
    FireworkProperties fireworkProps;
    bool testMode;

signals:
    /**
     * @brief – Informs the FireworkSandbox UI to re-enable buttons when appropriate
     */
    void enableButtons();

public slots:
    /**
     * @brief – Launches the firework shell
     */
    void launchRocket();

    /**
     * @brief – Changes the display background
     */
    void changeBackground(QString imagePath);

    /**
     * @brief – Creates an explosion according to the desired firework properties
     */
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
    /**
     * @brief – Custom paintEvent reimplementation that draws objects based on their
     * position in the Box2D physics simulation.
     */
    void paintEvent(QPaintEvent *);

    /**
     * @brief – Handles sizing this widget and the box2D world upon a resize event.
     */
    void resizeEvent(QResizeEvent* event);
};


#endif // FIREWORKSCENEWIDGET_H
