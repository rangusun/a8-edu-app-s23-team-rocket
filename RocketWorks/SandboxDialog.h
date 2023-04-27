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
    explicit SandboxDialog(QWidget *parent = nullptr);
    ~SandboxDialog();

private:
    Ui::SandboxDialog *ui;
};

#endif // SANDBOXDIALOG_H
