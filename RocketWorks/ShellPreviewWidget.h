#ifndef SHELLPREVIEWWIDGET_H
#define SHELLPREVIEWWIDGET_H

#include <QWidget>
#include "FireworkProperties.h"

class ShellPreviewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ShellPreviewWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);

    void setFireworkProperties(FireworkProperties *fireworkProps);

private:
    QImage background;

    FireworkProperties *fireworkProps;

    void drawStarLineBetweenPoints(QPainter &painter, QPoint point1, QPoint point2, float starDiameter);
    void drawStarCircle(QPainter &painter, float shellDiameter, float starDiameter, int numStars,
                       float screenCenterX, float screenCenterY);
    void drawStarHeart(QPainter &painter, float shellDiameter, float starDiameter, int numStars,
                       float screenCenterX, float screenCenterY);
    void drawStarStar(QPainter &painter, float shellDiameter, float starDiameter, int numStars,
                       float screenCenterX, float screenCenterY);
    void drawStarSmiley(QPainter &painter, float shellDiameter, float starDiameter, int numStars,
                      float screenCenterX, float screenCenterY);

protected:
    void resizeEvent(QResizeEvent* event);
};

#endif // SHELLPREVIEWWIDGET_H
