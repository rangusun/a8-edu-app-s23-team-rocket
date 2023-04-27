#ifndef FIREWORKTESTMODE_H
#define FIREWORKTESTMODE_H

#include <QWidget>
#include "TestModeModel.h"
#include "TestModeDialog.h"
#include "WinDialog.h"
#include <QDialogButtonBox>

namespace Ui {
class FireworkTestMode;
}

class FireworkTestMode : public QWidget
{
    Q_OBJECT

public:
    explicit FireworkTestMode(QWidget *parent = nullptr);
    ~FireworkTestMode();

private:
    Ui::FireworkTestMode *ui;

    TestModeModel model;

    TestModeDialog testModeDialog;
    WinLoseDialog winLoseDialog;
    bool visited;

signals:
    void changeToSandbox();

public slots:
    void startTestMode();
    void displaySpecificationsDialog(QString shapeSpec, QString colorSpec, QString soundSpec, int shellDiameterSpec);
    void updateOrdersFulfilled(int ordersFulfilled);
    void displayOrderCorrect(bool orderCorrect);

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void switchToSandbox();
    void listSpecifications(QString shapeSpec, QString colorSpec, QString soundSpec, int shellDiameterSpec);
};

#endif // FIREWORKTESTMODE_H
