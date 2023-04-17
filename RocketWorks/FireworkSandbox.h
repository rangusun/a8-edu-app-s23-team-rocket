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

private:
    Ui::FireworkSandbox *ui;
};

#endif // FIREWORKSANDBOX_H
