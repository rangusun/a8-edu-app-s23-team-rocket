#ifndef LAB10_H
#define LAB10_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Lab10; }
QT_END_NAMESPACE

class Lab10 : public QWidget
{
    Q_OBJECT

public:
    Lab10(QWidget *parent = nullptr);
    ~Lab10();
    void paintEvent(QPaintEvent *);

private:
    Ui::Lab10 *ui;

public slots:
    void valuesChanged();
};
#endif // LAB10_H
