#include "B2DWorldWrapper.h"

B2DWorldWrapper::B2DWorldWrapper (int screenWidth, int screenHeight) :
    world(b2Vec2(0.0f, -10.0f)), screenWidth{screenWidth}, screenHeight{screenHeight}
{
    // We need to track coordinates relative to the box2d engine
    // as well as the screen that objects will be painted on.
    // Our internal world size should have the same aspect ratio
    // as the screen.
    virtualHeight = virtualWidth * (screenHeight / screenWidth);

    // Make the ground for the world
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(virtualWidth / 2, -10.0f);

    b2Body* groundBody = world.CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    // Ground box is 100 units wide and 20 units tall
    groundBox.SetAsBox(virtualWidth / 2, 10.0f);

    groundBody->CreateFixture(&groundBox, 0.0f);


    //std::pair<string, b2Body*> groundMapping("ground", groundBody);
    worldObjects["ground"] = groundBody;

    std::pair<int, int> dimensions{virtualWidth, 20 * (virtualHeight / screenHeight) };
    //std::pair<string, std::pair<int, int>> dimensionsMapping("ground", dimensions);
    //objectDimensions.insert(dimensionsMapping);
    objectDimensions["ground"] = dimensions;
}

void B2DWorldWrapper::addObject(WorldObject newObject)
{
    // Create a dynamic body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(newObject.x * (virtualWidth / screenWidth), newObject.y * (virtualHeight / screenHeight));
    b2Body* body = world.CreateBody(&bodyDef);

    // Create a box shape for the body
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(newObject.width * (virtualWidth / screenWidth), newObject.height * (virtualHeight / screenHeight));

    // Create a fixture definition using the box shape
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    //Create a fixture for the body
    body->CreateFixture(&fixtureDef);

    // Add the new dynamic-body object to the list of world objects
    // to keep track of
    //std::pair<string, b2Body*> objectMapping(newObject.name, body);
    //worldObjects.insert(objectMapping);
    worldObjects[newObject.name] = body;

    std::pair<int, int> dimensions{newObject.width, newObject.height};

    //std::pair<string, std::pair<int, int>> dimensionsMapping("ground", dimensions);
    //objectDimensions.insert(newObject.name, dimensions);
    objectDimensions[newObject.name] = dimensions;
}

WorldObject B2DWorldWrapper::getObject(string name)
{
    WorldObject foundObject;
    auto worldObjIter = worldObjects.find(name);
    if (worldObjIter == worldObjects.end())
    {
        foundObject.name = "NotFound";
        return foundObject;
    }

    b2Body* foundBody = worldObjIter->second;
    foundObject.name = worldObjIter->first;
    foundObject.x = foundBody->GetPosition().x * (screenWidth / virtualWidth);
    foundObject.y = foundBody->GetPosition().y * (screenHeight / virtualHeight);

    foundObject.width = objectDimensions.find(name)->second.first;
    foundObject.height = objectDimensions.find(name)->second.second;
    return foundObject;
}

void B2DWorldWrapper::applyForceToObject(string name, int x, int y)
{

}

void B2DWorldWrapper::startWorldUpdates()
{
    connect(&timer, &QTimer::timeout, this, &B2DWorldWrapper::updateWorld);
    timer.start(10);
}

void B2DWorldWrapper::updateWorld()
{
    world.Step(1.0/60.0, 8, 3);
}

std::map<string, WorldObject> B2DWorldWrapper::getAllObjects()
{
    return std::map<string, WorldObject>();
}
