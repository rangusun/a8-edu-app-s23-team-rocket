#ifndef SHELLPREVIEWWIDGET_H
#define SHELLPREVIEWWIDGET_H

#include <QWidget>
#include "FireworkProperties.h"

class ShellPreviewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ShellPreviewWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);

    void setFireworkProperties(FireworkProperties *fireworkProps);

private:
    QImage background;

    FireworkProperties *fireworkProps;

protected:
    void resizeEvent(QResizeEvent* event);
};

#endif // SHELLPREVIEWWIDGET_H
