/**
 *  A8: An-Educational-App
 *
 *  @brief Popup dialog to inform the user they are in the test mode
 *         and will give them orders to fullfill.
 *
 *  By Anna Madsen, Carlos Gonzalez, Carter Edginton, Rachel Nguyen, and Zander Ruiz
 *  for CS 3505 in Spring 2023
*/
#ifndef TESTMODEDIALOG_H
#define TESTMODEDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class TestModeDialog;
}

class TestModeDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief – Constructor that initializes a TesModeDialog object.
     *
     */
    explicit TestModeDialog(QWidget *parent = nullptr);

    /**
     * @brief – Destructor that initializes a TesModeDialog object.
     *
     */
    ~TestModeDialog();

signals:
    /**
     * @brief changeToSandbox notifies the view that the user wants to switch to the sandbox level
     */
    void changeToSandbox();

    /**
     * @brief enableButtons notifies the view that the user is done reading dialog and that simulater buttons can be enabled
     */
    void enableButtons();

public slots:
    /**
     * @brief displaySpecificationsDialog displays the given specifications in a user-friendly format on this dialog
     * @param shapeSpec the shape of firework to tell the user to build
     * @param colorSpec the color of firework to tell the user to build
     * @param soundSpec the sound effect that the user's firework should make
     * @param shellDiameterSpec the size of firework that the user should make
     */
    void displaySpecificationsDialog(QString shapeSpec, QString colorSpec, QString soundSpec, int shellDiameterSpec);

    /**
     * @brief switchToSandbox receives a signal from a "Back to Sanbox" button on this dialog
     */
    void switchToSandbox();

protected:
    /**
     * @brief – Custom paintEvent reimplementation that draws
     *          The items for the dialog box.
     */
    void paintEvent(QPaintEvent *);

private:
    Ui::TestModeDialog *ui;
};

#endif // TESTMODEDIALOG_H
