/**
 *  A8: An-Educational-App
 *
 *  @brief A wrapper class that makes creating objects in Box2D easier.
 *
 *
 *  By
 *  for CS 3505 in Spring 2023
*/
#include <Box2D/Box2D.h>
#include <QTimer>
#include <tuple>
#include <string>
#include <map>
#include "WorldObject.h"


using std::string;
using std::map;

#ifndef B2DWORLDWRAPPER_H
#define B2DWORLDWRAPPER_H

class B2DWorldWrapper : public QObject
{
    Q_OBJECT
private:
    b2World world;
    map<string, b2Body*> worldObjects;
    map<string, std::pair<double, double>> objectDimensions;

    double screenWidth;
    double screenHeight;
    double zoom;

    QTimer timer;
public:
    explicit B2DWorldWrapper();
    map<string, WorldObject> getAllObjects();

    /**
     * @brief – Adds a WorldObject to the Box2D world.
     *
     *
     * @param WorldObject newObject- The object you want to add to the box2D world.
     */
    void addObject(WorldObject newObject);

    /**
     * @brief – Removes a WorldObject from the Box2D world.
     *
     *
     * @param string name- The name of the object you want to remove from the box2D world.
     */
    void removeObject(string name);

    /**
     * @brief – Finds the object from the Box2D world and returns it.
     *
     *
     * @param string name - The name of the object you want to grab from the box2D world.
     * @return A WorldObject item from the Box2D world.
     */
    WorldObject getObject(string name);

    /**
     * @brief – Applies a force to an Object in the Box2D world.
     *
     *
     * @param string name- The name of the object you want to apply the force to.
     * @param int x - The x value for the force vector.
     * @param int y - The y value for the force vector.
     */
    void applyForceToObject(string name, int x, int y);

    /**
     * @brief – Begins the timmer that updates the Box2D world.
     *
     */
    void startWorldUpdates();

    /**
     * @brief – Initializes the Box2D world and creates the ground.
     *
     *
     * @param double screenWidth - The screen width value in cartesian (Box2D) units.
     * @param double screenHieght - The screen height value in cartesian (Box2D) units.
     * @param double zoom - Adjusts how zoomed into the world we are in the window.
     */
    void initializeWorld(double screenWidth, double screenHeight, double zoom);

signals:
    void worldUpdated();

private slots:
    void updateWorld();
};

#endif // B2DWORLDWRAPPER_H
