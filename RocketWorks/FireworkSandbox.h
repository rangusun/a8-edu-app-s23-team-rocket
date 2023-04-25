#ifndef FIREWORKSANDBOX_H
#define FIREWORKSANDBOX_H

#include <QWidget>
#include "FireworkSceneWidget.h"
#include "FireworkShapeEnum.h"
#include "FireworkProperties.h"

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
private:
    Ui::FireworkSandbox *ui;
};

#endif // FIREWORKSANDBOX_H
