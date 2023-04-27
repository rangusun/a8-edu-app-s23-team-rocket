/**
 *  A8: An-Educational-App
 *
 *  @brief Popup dialog to celebrate the user fulfilling 3 correct orders
 *
 *  By Anna Madsen, Carlos Gonzalez, Carter Edginton, Rachel Nguyen, and Zander Ruiz
 *  for CS 3505 in Spring 2023
*/
#ifndef WINDIALOG_H
#define WINDIALOG_H

#include <QDialog>

namespace Ui {
class WinDialog;
}

class WinDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief – Constructor for WinDialog.
     */
    explicit WinDialog(QWidget *parent = nullptr);

    /**
     * @brief – Destructs WinDialog.
     */
    ~WinDialog();

signals:
    /**
     * @brief – Informs appropriate slots to go to sandbox when sandbox button clicked.
     */
    void backToSandbox();

public slots:
    /**
     * @brief – Handles closing and switching to sandbox when button clicked.
     */
    void switchToSandbox();

private:
    Ui::WinDialog *ui;
};

#endif // WINDIALOG_H
