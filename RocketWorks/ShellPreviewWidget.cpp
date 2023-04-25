#include "ShellPreviewWidget.h"
#include <QPainter>
#include <QDebug>

ShellPreviewWidget::ShellPreviewWidget(QWidget *parent)
    : QWidget{parent},
    background(":/FireworkResources/Resources/paperBackground.png")
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

    double shellDiameter = (fireworkProps->getShellDiameter() * 8.89) + 18.33;
    double screenCenterX = width()/2.0;
    double screenCenterY = height()/2.0;

    qDebug() << "Updating! Shell diameter:" << shellDiameter;

    QPen shellPen(QColor(255, 61, 126));
    shellPen.setWidth(4);
    painter.setPen(shellPen);
    painter.drawEllipse(screenCenterX - shellDiameter/2.0, screenCenterY - shellDiameter/2.0, shellDiameter, shellDiameter);

    QColor starColor = fireworkProps->getParticleColor();
    double starDiameter = 10;
    int numStars = 0.18 * shellDiameter;
    painter.setPen(starColor);
    painter.setBrush(starColor);
    QVector<QPoint> starPositions;

    for (int i = 0; i < numStars; i++)
    {
        double angle = 2 * M_PI * i / double(numStars);
        int x = static_cast<int>(screenCenterX + (shellDiameter/2.0 - 8) * cos(angle));
        int y = static_cast<int>(screenCenterY + (shellDiameter/2.0 - 8) * sin(angle));
        painter.drawEllipse(x - starDiameter/2.0, y - starDiameter/2.0, starDiameter, starDiameter);
    }

    painter.end();
}

void ShellPreviewWidget::setFireworkProperties(FireworkProperties *fireworkProps)
{
    qDebug() << "Old firework props:" << this->fireworkProps;

    this->fireworkProps = fireworkProps;

    qDebug() << "New firework props:" << this->fireworkProps;

    // Connections to fireworkProps go here
}

void ShellPreviewWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    background = QImage(":/FireworkResources/Resources/paperBackground.png");
    background = background.scaled(this->width(), this->height());
    update();
}


