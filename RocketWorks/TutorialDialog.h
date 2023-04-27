/**
 *  A8: An-Educational-App
 *
 *  @brief This class will hold all the Dialog for the Tutorial.
 *
 *
 *  By
 *  for CS 3505 in Spring 2023
*/
#ifndef TUTORIALDIALOG_H
#define TUTORIALDIALOG_H

#include <QDialog>
#include <QPixmap>
#include "TutorialComponents.h"

namespace Ui {
class TutorialDialog;
}

class TutorialDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief – Constructor for Tutorial Dialog.
     *
     *
     */
    explicit TutorialDialog(QWidget *parent = nullptr);

    /**
     * @brief – Destructor for Tutorial Dialog.
     *
     *
     */
    ~TutorialDialog();

    /**
     * @brief – Sets the ui to show component dialog.
     *
     *
     * @param - RocketComponent component - The type of component the user is looking at.
     */
    void showComponentDialog(RocketComponent component);

private:
    Ui::TutorialDialog *ui;

    QPixmap image;
    QString text;
    QString title;

    /**
     * @brief – Getter for component text information.
     *
     * @param - RocketComponent component - The type of component the user is looking at.
     * @return QString
     */
    QString getText(RocketComponent component);

    /**
     * @brief – Getter for component title information.
     *
     * @param - RocketComponent component - The type of component the user is looking at.
     */
    QString getTitle(RocketComponent component);

    /**
     * @brief – Getter for component image information.
     *
     * @param - RocketComponent component - The type of component the user is looking at.
     */
    QPixmap getImage(RocketComponent component);
};

#endif // TUTORIALDIALOG_H
