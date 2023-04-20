#include <Box2D/Box2D.h>
#include <QTimer>
#include <tuple>
#include <string>
#include <map>


using std::string;
using std::map;

#ifndef B2DWORLDWRAPPER_H
#define B2DWORLDWRAPPER_H
struct WorldObject
{
    string name;
    int x, y;
    int width, height;

    explicit WorldObject();
    explicit WorldObject(string name, int x, int y, int width, int height);
};

class B2DWorldWrapper : public QObject
{
    Q_OBJECT
private:
    b2World world;
    map<string, b2Body*> worldObjects;
    map<string, std::pair<int, int>> objectDimensions;
    double screenWidth;
    double screenHeight;
    float virtualWidth = 100;
    float virtualHeight;


    QTimer timer;
public:
    explicit B2DWorldWrapper (double screenWidth, double screenHeight);

    void addObject(WorldObject newObject);
    WorldObject getObject(string name);
    map<string, WorldObject> getAllObjects();
    void applyForceToObject(string name, int x, int y);


    void startWorldUpdates();

signals:
    void worldUpdated();

private slots:
    void updateWorld();
};

#endif // B2DWORLDWRAPPER_H
