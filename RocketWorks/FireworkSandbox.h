#ifndef FIREWORKSANDBOX_H
#define FIREWORKSANDBOX_H

#include <QWidget>
#include "FireworkSceneWidget.h"
#include "FireworkShapeEnum.h"
#include "FireworkProperties.h"

namespace Ui {
class FireworkSandbox;
}

class FireworkSandbox : public QWidget
{
    Q_OBJECT

public:
    explicit FireworkSandbox(QWidget *parent = nullptr);
    ~FireworkSandbox();

signals:
    void launch(FireworkProperties &fireworkProps);

public slots:
    void changeBackground(int checked);
    void disableButtons();
    void enableButtons();
    void switchModes(QString mode);

private:
    Ui::FireworkSandbox *ui;
    QImage controlPanelBackground;

protected:
    void paintEvent(QPaintEvent *);
};

#endif // FIREWORKSANDBOX_H
