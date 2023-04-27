/**
 *  A8: Educational-App
 *
 *  @brief UI wrapper containing a FireworkSandbox widget in "test" mode.
 *
 *  Test mode gives users "client orders" that they must fill, building a custom
 *  rocket with the shape, color, sound, and size specified by the client. Test
 *  mode limits the user from seeing what color/sound each material corresponds
 *  to when building the firework.
 *
 *  By Anna Madsen, Carlos Gonzalez, Carter Edginton, Rachel Nguyen, and Zander Ruiz
 *  for CS 3505 in Spring 2023
*/
#ifndef FIREWORKTESTMODE_H
#define FIREWORKTESTMODE_H

#include <QWidget>
#include "TestModeModel.h"
#include "TestModeDialog.h"
#include "WinDialog.h"
#include <QDialogButtonBox>

namespace Ui {
class FireworkTestMode;
}

class FireworkTestMode : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief – Creates a new FireworkTestMode
     */
    explicit FireworkTestMode(QWidget *parent = nullptr);

    /**
     * @brief – Destructs a FireworkTestMode
     */
    ~FireworkTestMode();

private:
    Ui::FireworkTestMode *ui;

    TestModeModel model;

    TestModeDialog testModeDialog;
    WinDialog winDialog;
    bool visited;

signals:
    /**
     * @brief – Signals to appropriate slots to change to sandbox mode.
     */
    void changeToSandbox();

public slots:
    /**
     * @brief – Informs the test model to create a new client order.
     *
     * Also disables appropriate buttons for when a test is active.
     */
    void startTestMode();

    /**
     * @brief – Displays the order specifications in a custom message from the "client"
     *
     * @param QString shapeSpec - firework shape
     * @param QString colorSpec - firework color
     * @param QString soundSpec - firework sound
     * @param int shellDiameterSpec - shell diameter
     */
    void displaySpecificationsDialog(QString shapeSpec, QString colorSpec, QString soundSpec, int shellDiameterSpec);

    /**
     * @brief – Displays the number of orders fulfilled thus far when a new order is fulfilled.
     *
     * Orders fulfilled maxes at at 3 on the display.
     */
    void updateOrdersFulfilled(int ordersFulfilled);

    /**
     * @brief – Informs user whether order was filled correctly with a breif custom message
     */
    void displayOrderCorrect(bool orderCorrect);

protected:
    /**
     * @brief – Paints the order slip under the client order.
     */
    void paintEvent(QPaintEvent *);

private slots:
    /**
     * @brief – Emits changeToSandbox signal, passing along message
     */
    void switchToSandbox();

    /**
     * @brief – Writes out the specifications in the specifications window
     */
    void listSpecifications(QString shapeSpec, QString colorSpec, QString soundSpec, int shellDiameterSpec);
};

#endif // FIREWORKTESTMODE_H
