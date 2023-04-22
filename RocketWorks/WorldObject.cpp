#include "WorldObject.h"

double WorldObject::screenWidth = 0;
double WorldObject::screenHeight = 0;
double WorldObject::zoom = 10;

void WorldObject::setScreenWidthAndHeight(double screenWidth, double screenHeight)
{
    WorldObject::screenWidth = screenWidth;
    WorldObject::screenHeight = screenHeight;
}

void WorldObject::setZoom(double zoom)
{
    WorldObject::zoom = zoom;
}

WorldObject WorldObject::makeWorldObjectfromCartCoords(string name, double x, double y, double width, double height)
{
    double pixelX = screenWidth/2.0 + x;
    double pixelY = screenHeight/2.0 - y;

    double drawX = pixelX - width/2.0;
    double drawY = pixelY - height/2.0;

    double box2DX = x / zoom;
    double box2DY = y / zoom;

    return WorldObject(name, x, y, pixelX, pixelY, drawX, drawY, box2DX, box2DY, width, height);
}

WorldObject WorldObject::makeWorldObjectfromPixelCoords(string name, double x, double y, double width, double height)
{
    double cartX = x - screenWidth/2.0;
    double cartY = y + screenHeight/2.0;

    double box2DX = cartX / zoom;
    double box2DY = cartY / zoom;

    double drawX = x - width/2.0;
    double drawY = y - height/2.0;

    return WorldObject(name, cartX, cartY, x, y, drawX, drawY, box2DX, box2DY, width, height);
}

WorldObject WorldObject::makeWorldObjectFromBox2DCoords(string name, double x, double y, double width, double height)
{
    double cartX = x * zoom;
    double cartY = x * zoom;

    double pixelX = screenWidth/2.0 + cartX;
    double pixelY = screenHeight/2.0 - cartY;

    double drawX = screenWidth/2.0 + zoom * (x - width/2.0);
    double drawY = screenHeight/2.0 - zoom * (y + height/2.0);

    return WorldObject(name, cartX, cartY, pixelX, pixelY, drawX, drawY, x, y, width * zoom, height * zoom);
}

WorldObject::WorldObject(string name, double cartX, double cartY, double pixelX, double pixelY, double drawX,
                         double drawY, double box2DX, double box2DY, double width, double height) :
    name(name), cartX(cartX), cartY(cartY), pixelX(pixelX), pixelY(pixelY), drawX(drawX),
    drawY(drawY), box2DX(box2DX), box2DY(box2DY), width(width), height(height) {}
