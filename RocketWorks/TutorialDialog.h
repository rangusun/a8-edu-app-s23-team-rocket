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
    explicit TutorialDialog(QWidget *parent = nullptr);
    ~TutorialDialog();

    void showComponentDialog(RocketComponent component);

private:
    Ui::TutorialDialog *ui;

    QPixmap image;
    QString text;
    QString title;

    QString getText(RocketComponent component);
};

#endif // TUTORIALDIALOG_H
