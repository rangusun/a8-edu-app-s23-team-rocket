/**
 *  A8: Educational-App
 *
 *  @brief UI for building and displaying a firework.
 *
 *  By Anna Madsen, Carlos Gonzalez, Carter Edginton, Rachel Nguyen, and Zander Ruiz
 *  for CS 3505 in Spring 2023
*/
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
    /**
     * @brief – Creates a new FireworkSandbox
     */
    explicit FireworkSandbox(QWidget *parent = nullptr);

    /**
     * @brief – Destructs a FireworkSandbox
     */
    ~FireworkSandbox();

signals:
    /**
     * @brief – Sends firework properties to subscribed slots upon launch.
     */
    void launch(FireworkProperties &fireworkProps);

public slots:
    /**
     * @brief – Changes the background of the firework display.
     */
    void changeBackground(int checked);

    /**
     * @brief – Disables firework editing buttons.
     */
    void disableButtons();

    /**
     * @brief – Enables firework editing buttons.
     */
    void enableButtons();

    /**
     * @brief – Changes certain logic in the sandbox UI depending on whether sandbox or testing mode is enabled.
     */
    void switchModes(QString mode);

private:
    Ui::FireworkSandbox *ui;
    QImage controlPanelBackground;
};

#endif // FIREWORKSANDBOX_H
