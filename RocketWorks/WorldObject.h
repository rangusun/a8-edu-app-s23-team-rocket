/**
 *  A8: An-Educational-App
 *
 *  @brief This class holds information about a WorldObject object and
 *  holds functions that can make these objects from pixel, cartesian, and Box2D coordinates.
 *
 *
 *  By
 *  for CS 3505 in Spring 2023
*/
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

    /**
     * @brief – Setter for the screen width and height.
     *
     *
     * @param double screenWidth – The screen width.
     * @param double screenHeight – The screen height.
     */
    static void setScreenWidthAndHeight(double screenWidth, double screenHeight);

    /**
     * @brief – Setter for the zoom value.
     *
     *
     * @param double zoom - The zoom value.
     */
    static void setZoom(double zoom);

    /**
     * @brief – Creates a WorldObject using Cartesian coordniates.
     *
     * @param string name - The name of the object being created.
     * @param double x - X cartesian value.
     * @param double y - Y cartesian value.
     * @param double width - Object width.
     * @param double height - Object height.
     * @return WorldObject
     */
    static WorldObject makeWorldObjectFromCartCoords(string name, double x, double y, double width, double height);

    /**
     * @brief – Creates a WorldObject using Pixel coordniates.
     *
     * @param string name - The name of the object being created.
     * @param double x - X pixel value.
     * @param double y - Y pixel value.
     * @param double width - Object width.
     * @param double height - Object height.
     * @return WorldObject
     */
    static WorldObject makeWorldObjectfromPixelCoords(string name, double x, double y, double width, double height);

    /**
     * @brief – Creates a WorldObject using Box2D coordniates.
     *
     * @param string name - The name of the object being created.
     * @param double x - X Box2D value.
     * @param double y - Y Box2D value.
     * @param double width - Object width.
     * @param double height - Object height.
     * @return WorldObject
     */
    static WorldObject makeWorldObjectFromBox2DCoords(string name, double x, double y, double width, double height);

private:
    /**
     * @brief – Creates a WorldObject object.
     *
     * @param string name - The name of the object being created.
     * @param double cartX - X cartesian value.
     * @param double cartY - Y cartesian value.
     * @param double pixelX - X pixel value.
     * @param double pixelY - Y pixel value.
     * @param double drawX - Drawing x value.
     * @param double drawY - Drawing y value.
     * @param double box2DX - X Box2D value.
     * @param double box2DY - Y Box2D value.
     * @param double width - Object width.
     * @param double height - Object height.
     * @return WorldObject
     */
    explicit WorldObject(string name, double cartX, double cartY, double pixelX, double pixelY, double drawX,
                         double drawY, double box2DX, double box2DY, double width, double height);
};

#endif // WORLDOBJECT_H
