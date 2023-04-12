
#ifndef FIREWORKSIM_H
#define FIREWORKSIM_H

#include <QMainWindow>



QT_BEGIN_NAMESPACE
namespace Ui { class FireworkSim; }
QT_END_NAMESPACE

class FireworkSim : public QMainWindow

{
    Q_OBJECT

public:
    FireworkSim(QWidget *parent = nullptr);
    ~FireworkSim();

private:
    Ui::FireworkSim *ui;
};

#endif // FIREWORKSIM_H
