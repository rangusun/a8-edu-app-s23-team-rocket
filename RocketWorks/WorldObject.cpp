/**
 *  A8: An-Educational-App
 *
 *  @brief This class holds information about a WorldObject object and
 *  holds functions that can make these objects from pixel, cartesian, and Box2D coordinates.
 *
 *  All coordinates are autotranslated to make converting on-screen coordinates to box2d coordinates
 *  or different on-screen coordinate systems.
 *
 *  Cartesian, pixel, and draw coordinates are all by pixel units according to positions on the screen.
 *  Pixel coordinates are from 0, 0 at the top left with down as the positive Y and left as the positive X.
 *  Draw coordinates are the pixel coordinates translated by half the object width and height so objects
 *  can be drawn correctly from the top left corner.
 *
 *  By Anna Madsen, Carlos Gonzalez, Carter Edginton, Rachel Nguyen, and Zander Ruiz
 *  for CS 3505 in Spring 2023
*/
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

WorldObject WorldObject::makeWorldObjectFromCartCoords(string name, double x, double y, double width, double height)
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
    double cartY = y * zoom;

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
