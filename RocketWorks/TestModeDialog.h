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
    void changeToSandbox();
    void enableButtons();

public slots:
    void displaySpecificationsDialog(QString shapeSpec, QString colorSpec, QString soundSpec, int shellDiameterSpec);
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
