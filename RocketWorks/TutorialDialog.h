#ifndef TUTORIALDIALOG_H
#define TUTORIALDIALOG_H

#include <QDialog>
#include <QPixmap>

namespace Ui {
class TutorialDialog;
}

class TutorialDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TutorialDialog(QString imagePath, QString text, QString title, QWidget *parent = nullptr);
    ~TutorialDialog();

private:
    Ui::TutorialDialog *ui;

    QPixmap image;
    QString text;
    QString title;
};

#endif // TUTORIALDIALOG_H
