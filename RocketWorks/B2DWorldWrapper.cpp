/**
 *  A8: Educational-App
 *
 *  @brief A wrapper class that makes creating and tracking objects in Box2D easier.
 *
 *  By Anna Madsen, Carlos Gonzalez, Carter Edginton, Rachel Nguyen, and Zander Ruiz
 *  for CS 3505 in Spring 2023
*/
#include "B2DWorldWrapper.h"


B2DWorldWrapper::B2DWorldWrapper() : world(b2Vec2(0.0f, -28.0f)), screenWidth(100.0), screenHeight(100.0), zoom(1.0) {}

void B2DWorldWrapper::initializeWorld(double screenWidth, double screenHeight, double zoom)
{
    // Let world object know about the screen width and height and the desired zoom so that it can
    // perform calculations correctly. "Zoom" adjusts how zoomed into the world we are in the window
    WorldObject::setScreenWidthAndHeight(screenWidth, screenHeight);

    // If the zoom is given as 0, set it to 1 (if zoom > 0, don't change zoom, else set it to 1)
    zoom = zoom > 0.0 ? zoom : 1.0;
    WorldObject::setZoom(zoom);

    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->zoom = zoom;

    // Make the ground for the world -------------------------------------------------

    // NOTE: Width, Height, X, and Y for the ground are all calculated to be in cartesian (Box2D) units

    // Set the values for the ground. Ground box is twice the width of the screen (just so that it stretches
    // past the edges of the screen) and 40 pixels tall (its world height will depend on the zoom chosen; this
    // essentially ensures that no matter what zoom is chosen, the top of the ground will show as 20 pixels
    // above the bottom of the screen)
    //    float groundWidth = screenWidth / zoom;
    //    float groundHeight = 20.0 / zoom;

    double groundWidth = screenWidth / zoom;
    double groundHeight = 20.0 / zoom;

    // The ground is set at the center bottom of the screen. The math for the y pos ensures that the center of the
    // ground will be set centered exactly on the bottom of the screen no matter what zoom factor is chosen (so the
    // top of the ground will show above the bottom of the screen a bit, but the bottom will be off screen)
    double groundXPos = 0.0;
    double groundYPos = (-screenHeight/2.0) / zoom;

    // Create the ground object and add it to the Box2D world
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(groundXPos, groundYPos);

    b2Body* groundBody = world.CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;

    groundBox.SetAsBox(groundWidth, groundHeight);
    groundBody->CreateFixture(&groundBox, 0.0f);

    worldObjects["ground"] = groundBody;

    std::pair<double, double> dimensions{ groundWidth * 2.0, groundHeight * 2.0 };

    objectDimensions["ground"] = dimensions;
}

void B2DWorldWrapper::addObject(WorldObject newObject)
{
    auto foundObject = worldObjects.find(newObject.name);

    if(foundObject != worldObjects.end())
    {
        world.DestroyBody(foundObject->second);
    }

    // Create a dynamic body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(newObject.box2DX, newObject.box2DY);
    b2Body* body = world.CreateBody(&bodyDef);

    // Create a box shape for the body
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox((newObject.width/zoom)/2.0, (newObject.height/zoom)/2.0);

    // Create a fixture definition using the box shape
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.9f;
    fixtureDef.restitution = 0.6f;

    //Create a fixture for the body
    body->CreateFixture(&fixtureDef);

    // Add the new dynamic-body object to the list of world objects
    // to keep track of
    worldObjects[newObject.name] = body;

    std::pair<double, double> dimensions{(newObject.width / zoom), (newObject.height / zoom)};

    objectDimensions[newObject.name] = dimensions;
}

void B2DWorldWrapper::removeObject(string name)
{
    auto foundObject = worldObjects.find(name);

    if(foundObject != worldObjects.end())
    {
        world.DestroyBody(foundObject->second);
    }
    worldObjects.erase(name);
}

WorldObject B2DWorldWrapper::getObject(string name)
{
    if (worldObjects.count(name) == 0)
    {
        return WorldObject::makeWorldObjectFromBox2DCoords("Not found", 1, 1, 1, 1);
    }

    double width = objectDimensions[name].first;
    double height = objectDimensions[name].second;
    b2Vec2 position = worldObjects[name]->GetPosition();

    return WorldObject::makeWorldObjectFromBox2DCoords(name, position.x, position.y, width, height);
}

void B2DWorldWrapper::applyForceToObject(string name, int x, int y)
{
    worldObjects[name]->ApplyForce(b2Vec2(x, y), b2Vec2(worldObjects[name]->GetPosition().x,worldObjects[name]->GetPosition().y), true);
}

void B2DWorldWrapper::startWorldUpdates()
{
    connect(&timer, &QTimer::timeout, this, &B2DWorldWrapper::updateWorld);
    timer.start(10);
}

void B2DWorldWrapper::updateWorld()
{
    world.Step(1.0/120.0, 6, 2);
    emit worldUpdated();
}

std::map<string, WorldObject> B2DWorldWrapper::getAllObjects()
{
    map<string, WorldObject> objects;

    for (auto& [name, body] : worldObjects)
    {
        double width = objectDimensions.find(name)->second.first;
        double height = objectDimensions.find(name)->second.second;
        b2Vec2 position = body->GetPosition();

        WorldObject object = WorldObject::makeWorldObjectFromBox2DCoords(name, position.x, position.y, width, height);
        objects.insert(std::pair<string, WorldObject>(name, object));
    }

    return objects;
}
