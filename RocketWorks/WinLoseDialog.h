#ifndef WINLOSEDIALOG_H
#define WINLOSEDIALOG_H

#include <QDialog>

namespace Ui {
class WinLoseDialog;
}

class WinLoseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WinLoseDialog(QWidget *parent = nullptr);
    ~WinLoseDialog();
signals:
    void backToSandbox();
    void newTest();
public slots:
    void switchToSandbox();
private:
    Ui::WinLoseDialog *ui;
};

#endif // WINLOSEDIALOG_H
