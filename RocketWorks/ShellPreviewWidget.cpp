#include "ShellPreviewWidget.h"
#include "FireworkShapeEnum.h"
#include <QPainter>
#include <QDebug>
#include <QPainterPath>

ShellPreviewWidget::ShellPreviewWidget(QWidget *parent)
    : QWidget{parent},
    showStarColor(true),
    background(":/ShellPreviewResources/Resources/ShellPreviewBackground.png")
{
    background = background.scaled(this->width(), this->height());
    setStyleSheet("border: 10px solid white");
}

void ShellPreviewWidget::paintEvent(QPaintEvent *)
{
    // Create a painter
    QPainter painter(this);

    // Draw background
    painter.drawImage(0, 0, background);

    // Draw the shell
    float shellDiameter = (fireworkProps->getShellDiameter() * 5.56) + 58.33;
    float screenCenterX = width()/2.0;
    float screenCenterY = height()/2.0;

    QPen shellPen(QColor(255, 61, 126));
    shellPen.setWidth(4);
    painter.setPen(shellPen);
    painter.drawEllipse(screenCenterX - shellDiameter/2.0, screenCenterY - shellDiameter/2.0, shellDiameter, shellDiameter);

    // Draw stars in the selected shape
    float starDiameter = 6;
    int numStars = (1.8 * shellDiameter) / starDiameter;

    if (showStarColor)
    {
        QColor starColor = fireworkProps->getParticleColor();
        painter.setPen(starColor);
        painter.setBrush(starColor);
    }

    // If star colors are not enabled, make stars grey like they would be irl
    else
    {
        QColor starColor(99, 99, 99);
        painter.setPen(starColor);
        painter.setBrush(starColor);
    }

    FireworkShape shape = fireworkProps->getShape();

    switch(shape)
    {
        case(circle):
            drawStarCircle(painter, shellDiameter, starDiameter, numStars, screenCenterX, screenCenterY);
            break;

        case(heart):
            drawStarHeart(painter, shellDiameter, starDiameter, numStars, screenCenterX, screenCenterY);
            break;

        case(star):
            drawStarStar(painter, shellDiameter, starDiameter, screenCenterX, screenCenterY);
            break;

        case(smile):
            drawStarSmiley(painter, shellDiameter, starDiameter, numStars, screenCenterX, screenCenterY);
            break;
    }

    painter.end();
}

void ShellPreviewWidget::drawStarLineBetweenPoints(QPainter &painter, QPoint point1, QPoint point2, float starDiameter)
{
    QPoint leftPoint = point1.x() < point2.x() ? point1 : point2;
    QPoint rightPoint = point1.x() < point2.x() ? point2 : point1;

    float dx = rightPoint.x() - leftPoint.x();
    float dy = rightPoint.y() - leftPoint.y();

    float slope = dy / dx;
    float increment = (starDiameter * 2) / qSqrt(1 + slope*slope);

    for (float i = 0; i < dx; i += increment)
    {
        float x = leftPoint.x() + i;
        int y = leftPoint.y() + slope * i;
        painter.drawEllipse(x - starDiameter/2.0, y - starDiameter/2.0, starDiameter, starDiameter);
    }
}

void ShellPreviewWidget::drawStarCircle(QPainter &painter, float shellDiameter, float starDiameter, int numStars,
                                        float screenCenterX, float screenCenterY)
{
    for (int i = 0; i < numStars; i++)
    {
        double angle = 2 * M_PI * i / double(numStars);
        int x = static_cast<int>(screenCenterX + (shellDiameter/2.0 - 8) * cos(angle));
        int y = static_cast<int>(screenCenterY + (shellDiameter/2.0 - 8) * sin(angle));
        painter.drawEllipse(x - starDiameter/2.0, y - starDiameter/2.0, starDiameter, starDiameter);
    }
}

void ShellPreviewWidget::drawStarHeart(QPainter &painter, float shellDiameter, float starDiameter, int numStars,
                                       float screenCenterX, float screenCenterY)
{
    painter.save();

    // Draw the left top of the heart
    painter.translate(-shellDiameter/5.0, -shellDiameter/8.0);
    for (int i = 0; i < numStars/6.0; i++)
    {
        double angle = 2 * M_PI * i / double(numStars/3.0) + M_PI * 1.025;
        int x = static_cast<int>(screenCenterX + (shellDiameter/4.0 - (4 + starDiameter/2.0)) * cos(angle));
        int y = static_cast<int>(screenCenterY + (shellDiameter/4.0 - (4 + starDiameter/2.0)) * sin(angle));
        painter.drawEllipse(x - starDiameter/2.0, y - starDiameter/2.0, starDiameter, starDiameter);
    }

    // Draw the right top of the heart
    painter.translate(2.0 * (shellDiameter/5.0), 0);
    for (int i = 0; i < numStars/6.0; i++)
    {
        double angle = 2 * M_PI * i / double(numStars/3.0);
        int x = static_cast<int>(screenCenterX + (shellDiameter/4.0 - (4 + starDiameter/2.0)) * cos(-angle));
        int y = static_cast<int>(screenCenterY + (shellDiameter/4.0 - (4 + starDiameter/2.0)) * sin(-angle));
        painter.drawEllipse(x - starDiameter/2.0, y - starDiameter/2.0, starDiameter, starDiameter);
    }

    painter.restore();

    // Draw the left bottom of the heart
    QPoint topLeftPoint(screenCenterX - (shellDiameter * 0.42 - (4 + starDiameter/2.0)), screenCenterY - shellDiameter * 0.025);
    QPoint bottomPoint(screenCenterX, screenCenterY + (shellDiameter/2.0 - (4 + starDiameter/2.0)));
    drawStarLineBetweenPoints(painter, topLeftPoint, bottomPoint, starDiameter);

    // Draw the right bottom of the heart
    QPoint topRightPoint(screenCenterX + (shellDiameter * 0.42 - (4 + starDiameter/2.0)), screenCenterY - shellDiameter * 0.0265);
    drawStarLineBetweenPoints(painter, bottomPoint, topRightPoint, starDiameter);
}

void ShellPreviewWidget::drawStarStar(QPainter &painter, float shellDiameter, float starDiameter, float screenCenterX, float screenCenterY)
{
    // Calculate star's outer points
    QVector<QPoint> outerPoints;
    for (int i = 0; i < 5; i++)
    {
        double angle = 2 * M_PI * i / 5.0 + M_PI * 1.5;
        int x = static_cast<int>(screenCenterX + (shellDiameter/2.0 - 8) * cos(angle));
        int y = static_cast<int>(screenCenterY + (shellDiameter/2.0 - 8) * sin(angle));
        outerPoints.push_back(QPoint(x, y));
    }

    // Calculate star's inner points
    QVector<QPoint> innerPoints;
    for (int i = 0; i < 5; i++)
    {
        double angle = 2 * M_PI * i / 5.0 + M_PI * 2.5;
        int x = static_cast<int>(screenCenterX + (shellDiameter/6.0) * cos(angle));
        int y = static_cast<int>(screenCenterY + (shellDiameter/6.0) * sin(angle));
        innerPoints.push_back(QPoint(x, y));
    }

    // Draw outer points
    for (QPoint point : outerPoints)
    {
        painter.drawEllipse(point.x() - starDiameter/2.0, point.y() - starDiameter/2.0, starDiameter, starDiameter);
    }

    // Connect points with lines
    for (int i = 0; i < 5; i++)
    {
        drawStarLineBetweenPoints(painter, outerPoints[i], innerPoints[(i + 3) % innerPoints.size()], starDiameter);
        drawStarLineBetweenPoints(painter, outerPoints[i], innerPoints[(i + 2) % innerPoints.size()], starDiameter);
    }
}

void ShellPreviewWidget::drawStarSmiley(QPainter &painter, float shellDiameter, float starDiameter, int numStars, float screenCenterX, float screenCenterY)
{
    for (int i = 0; i < numStars/2.0; i++)
    {
        float angle = 2 * M_PI * i / float(numStars) + M_PI * 0.05/(shellDiameter/50);
        int x = static_cast<int>(screenCenterX + (shellDiameter/2.0 - 8) * cos(angle));
        int y = static_cast<int>(screenCenterY + (shellDiameter/2.0 - 8) * sin(angle));
        painter.drawEllipse(x - starDiameter/2.0, y - starDiameter/2.0, starDiameter, starDiameter);
    }

    // Draw Left Eye
    int x = screenCenterX - shellDiameter/6.0;
    for (float y = screenCenterY; y > screenCenterY - (shellDiameter * 0.4) ; y -= starDiameter * 1.5)
    {
        painter.drawEllipse(x - starDiameter/2.0, y - starDiameter/2.0, starDiameter, starDiameter);
    }

    // Draw Right Eye
    x = screenCenterX + shellDiameter/6.0;
    for (float y = screenCenterY; y > screenCenterY - (shellDiameter * 0.4) ; y -= starDiameter * 1.5)
    {
        painter.drawEllipse(x - starDiameter/2.0, y - starDiameter/2.0, starDiameter, starDiameter);
    }
}

void ShellPreviewWidget::setFireworkProperties(FireworkProperties *fireworkProps)
{
    this->fireworkProps = fireworkProps;
}

void ShellPreviewWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    background = QImage(":/ShellPreviewResources/Resources/ShellPreviewBackground.png");
    background = background.scaled(this->width(), this->height());
    update();
}


