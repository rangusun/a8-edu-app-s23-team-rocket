#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include <string>

using std::string;

class WorldObject
{
private:
    static double screenWidth;
    static double screenHeight;
    static double zoom;

public:
    const string name;
    const double cartX, cartY;
    const double pixelX, pixelY;
    const double drawX, drawY;
    const double box2DX, box2DY;
    const double width, height;

    static void setScreenWidthAndHeight(double screenWidth, double screenHeight);
    static void setZoom(double zoom);

    static WorldObject makeWorldObjectFromCartCoords(string name, double x, double y, double width, double height);
    static WorldObject makeWorldObjectfromPixelCoords(string name, double x, double y, double width, double height);
    static WorldObject makeWorldObjectFromBox2DCoords(string name, double x, double y, double width, double height);

private:
    explicit WorldObject(string name, double cartX, double cartY, double pixelX, double pixelY, double drawX,
                         double drawY, double box2DX, double box2DY, double width, double height);
};

#endif // WORLDOBJECT_H
