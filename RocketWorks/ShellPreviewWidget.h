/**
 *  A8: An-Educational-App
 *
 *  @brief This class holds all the ShellPreview functions for drawing the Shell.
 *
 *
 *  By
 *  for CS 3505 in Spring 2023
*/
#ifndef SHELLPREVIEWWIDGET_H
#define SHELLPREVIEWWIDGET_H

#include <QWidget>
#include "FireworkProperties.h"

class ShellPreviewWidget : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief – Constructor for the ShellPreview Widget.
     *
     *
     */
    explicit ShellPreviewWidget(QWidget *parent = nullptr);

    /**
     * @brief – Paints the Shell and the starshape for the user to see.
     *
     *
     * @param QPaintEvent - A pointer to a QPaintEvent.
     */
    void paintEvent(QPaintEvent *);

    /**
     * @brief – Setter for the Firework properties.
     *
     *
     * @param FireworkProperties - The properties for the firework.
     */
    void setFireworkProperties(FireworkProperties *fireworkProps);

    bool showStarColor;

private:
    QImage background;

    FireworkProperties *fireworkProps;

    /**
     * @brief – This funtion will draw a star point between two points.
     *
     *
     * @param QPainter &Painter - The painter object used to draw on the widget.
     * @param Qpoint Point1 - The first point to begin drawing from.
     * @param Qpoint Point2 - The second point to finish the drawing.
     * @param floar starDiameter - The diameter of the star.
     */
    void drawStarLineBetweenPoints(QPainter &painter, QPoint point1, QPoint point2, float starDiameter);

    /**
     * @brief – This funtion will draw the stars into a shape of a circle.
     *
     *
     * @param QPainter &Painter - The painter object used to draw on the widget.
     * @param float shellDiameter - The shell diameter.
     * @param floar starDiameter - The diameter of the star.
     * @param int numStars - The number of stars needed to be drawn.
     * @param float screenCenterX - The screen center x value.
     * @param float screenCenterY - The screen center y value.
     */
    void drawStarCircle(QPainter &painter, float shellDiameter, float starDiameter, int numStars,
                       float screenCenterX, float screenCenterY);

    /**
     * @brief – This funtion will draw the stars into a heart shape.
     *
     *
     * @param QPainter &Painter - The painter object used to draw on the widget.
     * @param float shellDiameter - The shell diameter.
     * @param floar starDiameter - The diameter of the star.
     * @param int numStars - The number of stars needed to be drawn.
     * @param float screenCenterX - The screen center x value.
     * @param float screenCenterY - The screen center y value.
     */
    void drawStarHeart(QPainter &painter, float shellDiameter, float starDiameter, int numStars,
                       float screenCenterX, float screenCenterY);

    /**
     * @brief – This funtion will draw the stars into a star shape.
     *
     *
     * @param QPainter &Painter - The painter object used to draw on the widget.
     * @param float shellDiameter - The shell diameter.
     * @param floar starDiameter - The diameter of the star.
     * @param int numStars - The number of stars needed to be drawn.
     * @param float screenCenterX - The screen center x value.
     * @param float screenCenterY - The screen center y value.
     */
    void drawStarStar(QPainter &painter, float shellDiameter, float starDiameter,
                       float screenCenterX, float screenCenterY);

    /**
     * @brief – This funtion will draw the stars into smiley face shape.
     *
     *
     * @param QPainter &Painter - The painter object used to draw on the widget.
     * @param float shellDiameter - The shell diameter.
     * @param floar starDiameter - The diameter of the star.
     * @param int numStars - The number of stars needed to be drawn.
     * @param float screenCenterX - The screen center x value.
     * @param float screenCenterY - The screen center y value.
     */
    void drawStarSmiley(QPainter &painter, float shellDiameter, float starDiameter, int numStars,
                      float screenCenterX, float screenCenterY);

protected:
    /**
     * @brief – Will reseize the shellpreview window if its changed..
     *
     *
     * @param QResizeEvent* event - A pointer to a QResizeEvent object.
     */
    void resizeEvent(QResizeEvent* event);
};

#endif // SHELLPREVIEWWIDGET_H
