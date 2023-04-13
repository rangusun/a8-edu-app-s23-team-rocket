#ifndef TUTORIALDIALOG_H
#define TUTORIALDIALOG_H

#include <QDialog>

namespace Ui {
class TutorialDialog;
}

class TutorialDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TutorialDialog(QWidget *parent = nullptr);
    ~TutorialDialog();

private:
    Ui::TutorialDialog *ui;
};

#endif // TUTORIALDIALOG_H
