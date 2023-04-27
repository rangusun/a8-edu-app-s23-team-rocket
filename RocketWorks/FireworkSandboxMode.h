#ifndef FIREWORKSANDBOXMODE_H
#define FIREWORKSANDBOXMODE_H

#include "SandboxDialog.h"
#include <QWidget>

namespace Ui {
class FireworkSandboxMode;
}

class FireworkSandboxMode : public QWidget
{
    Q_OBJECT

public:
    explicit FireworkSandboxMode(QWidget *parent = nullptr);
    ~FireworkSandboxMode();
    bool visited;
    SandboxDialog sandboxDialog;

private:
    Ui::FireworkSandboxMode *ui;

signals:
    void changeToTestmode();

private slots:
    void switchToTestmode();
};

#endif // FIREWORKSANDBOXMODE_H
