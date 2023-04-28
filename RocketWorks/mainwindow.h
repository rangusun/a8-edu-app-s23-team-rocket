/**
 *  A8: An-Educational-App
 *
 *  @brief This is the main window that holds all the pages of the application.
 *         It displays one page at a time and can switch between the pages.
 *
 *  By Anna Madsen, Carlos Gonzalez, Carter Edginton, Rachel Nguyen, and Zander Ruiz
 *  for CS 3505 in Spring 2023
*/
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
    /**
     * @brief - Creates a new MainWindow.
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     *  @brief - Destructs a MainWindow.
     */
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    TutorialPage tutorialPage;
    FireworkSandboxMode sandboxPage;
    FireworkTestMode testPage;

public slots:
    /**
     * @brief - Switches the current page to the Sandbox page.
     */
    void switchToSandboxPage();

    /**
     * @brief - Switches the current page to the Test Mode page.
     */
    void switchToTestModePage();

};
#endif // MAINWINDOW_H
