#ifndef FIREWORKTESTMODE_H
#define FIREWORKTESTMODE_H

#include <QWidget>
#include "TestModeModel.h"
#include "TestModeDialog.h"

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

signals:
    void changeToSandbox();

public slots:
    void startTestMode();

private slots:
    void switchToSandbox();
};

#endif // FIREWORKTESTMODE_H
