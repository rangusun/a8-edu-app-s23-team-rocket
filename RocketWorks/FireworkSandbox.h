#ifndef FIREWORKSANDBOX_H
#define FIREWORKSANDBOX_H

#include <QWidget>
#include "FireworkSceneWidget.h"

namespace Ui {
class FireworkSandbox;
}

class FireworkSandbox : public QWidget
{
    Q_OBJECT

public:
    explicit FireworkSandbox(QWidget *parent = nullptr);
    ~FireworkSandbox();

public slots:
    void changeBackground(int checked);
    void sliderValueChange(int value);
    void colorDropdownChanged(QString color);
    void soundDropdownChanged(QString sound);
    void shapeDropdownChanged(QString shape);
private:
    int shellDiameter;
    QString currentColor;
    QString currentSound;
    QString currentShape;
    Ui::FireworkSandbox *ui;

};

#endif // FIREWORKSANDBOX_H
