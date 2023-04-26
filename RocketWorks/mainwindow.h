#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "TutorialPage.h"
#include "FireworkSandboxMode.h"
#include "FireworkTestMode.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    TutorialPage tutorialPage;
    FireworkSandboxMode sandboxPage;
    FireworkTestMode testPage;

public slots:
    void switchToSandboxPage();
    void switchToTestModePage();

};
#endif // MAINWINDOW_H
