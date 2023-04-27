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
    explicit TestModeDialog(QWidget *parent = nullptr);
    ~TestModeDialog();

signals:
    void changeToSandbox();
    void enableButtons();

public slots:
    void displaySpecificationsDialog(QString shapeSpec, QString colorSpec, QString soundSpec, int shellDiameterSpec);

    void switchToSandbox();


private:
    Ui::TestModeDialog *ui;
};

#endif // TESTMODEDIALOG_H
