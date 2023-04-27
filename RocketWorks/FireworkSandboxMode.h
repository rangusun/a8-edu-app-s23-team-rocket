/**
 *  A8: Educational-App
 *
 *  @brief UI wrapper containing a FireworkSandbox widget in "sandbox" mode.
 *
 *  Allows user to freely experiment with firework materials and settings to learn
 *  the different parts of a firework.
 *
 *  By Anna Madsen, Carlos Gonzalez, Carter Edginton, Rachel Nguyen, and Zander Ruiz
 *  for CS 3505 in Spring 2023
*/
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
    /**
     * @brief – Creates a new FireworkSandboxMode
     */
    explicit FireworkSandboxMode(QWidget *parent = nullptr);

    /**
     * @brief – Destructs a FireworkSandboxMode
     */
    ~FireworkSandboxMode();

    bool visited;
    SandboxDialog sandboxDialog;

private:
    Ui::FireworkSandboxMode *ui;

signals:
    /**
     * @brief – Informs subscribed slots to change the UI to test mode.
     */
    void changeToTestmode();

private slots:
    /**
     * @brief – Can be called to informs subscribed slots to change the UI to test mode.
     */
    void switchToTestmode();
};

#endif // FIREWORKSANDBOXMODE_H
