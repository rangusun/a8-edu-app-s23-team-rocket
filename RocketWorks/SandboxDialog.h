/**
 *  A8: An-Educational-App
 *
 *  @brief Popup dialog to inform the user about the sandbox mode.
 *
 *  By Anna Madsen, Carlos Gonzalez, Carter Edginton, Rachel Nguyen, and Zander Ruiz
 *  for CS 3505 in Spring 2023
*/
#ifndef SANDBOXDIALOG_H
#define SANDBOXDIALOG_H

#include <QDialog>

namespace Ui {
class SandboxDialog;
}

class SandboxDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief - Constructor for SandboxDialog object.
     *
     * @param QWidget* parent - A pointer to a QWidget object.
     */
    explicit SandboxDialog(QWidget *parent = nullptr);
    /**
     * @brief - Destructor for SandboxDialog object.
     */
    ~SandboxDialog();

private:
    Ui::SandboxDialog *ui;
};

#endif // SANDBOXDIALOG_H
