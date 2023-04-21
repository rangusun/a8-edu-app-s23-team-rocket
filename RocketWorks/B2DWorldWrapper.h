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

    void addObject(WorldObject newObject);
    WorldObject getObject(string name);
    map<string, WorldObject> getAllObjects();
    void applyForceToObject(string name, int x, int y);

    void startWorldUpdates();

    void initializeWorld(double screenWidth, double screenHeight, double zoom);

signals:
    void worldUpdated();

private slots:
    void updateWorld();
};

#endif // B2DWORLDWRAPPER_H
