#ifndef TESTMODEDIALOG_H
#define TESTMODEDIALOG_H

#include <QDialog>

namespace Ui {
class TestModeDialog;
}

class TestModeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TestModeDialog(QWidget *parent = nullptr);
    ~TestModeDialog();

public slots:
    void displaySpecificationsDialog(QString shapeSpec, QString colorSpec, QString soundSpec, int shellDiameterSpec);


private:
    Ui::TestModeDialog *ui;
};

#endif // TESTMODEDIALOG_H
