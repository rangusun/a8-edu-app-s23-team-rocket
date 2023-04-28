/**
 *  A8: Educational-App
 *
 *  @brief UI for teaching users about components of fireworks and what they do.
 *
 *  By Anna Madsen, Carlos Gonzalez, Carter Edginton, Rachel Nguyen, and Zander Ruiz
 *  for CS 3505 in Spring 2023
*/
#ifndef TUTORIALPAGE_H
#define TUTORIALPAGE_H

#include <QWidget>
#include <map>
#include "TutorialDialog.h"
#include "TutorialComponents.h"

using std::map;

namespace Ui {
class TutorialPage;
}

class TutorialPage : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief - Creates a new TutorialPage
     */
    explicit TutorialPage(QWidget *parent = nullptr);

    /**
     * @brief - Destructs a TutorialPage
     */
    ~TutorialPage();

private:
    Ui::TutorialPage *ui;

    TutorialDialog componentDialog;

    map<RocketComponent, bool> dialogsVisited;

    /**
     * @brief - Checks if the user has visited all the component dialogs before
     *          allowing them to proceed to the next level.
     */
    void CheckIfAllPagesVisited();

signals:
    /**
     * @brief - Sends a signal to switch to a different window/page.
     */
    void changePage();

private slots:
    /**
     * @brief - Changes the current page to the Sandbox page.
     */
    void switchToSandbox();

};

#endif // TUTORIALPAGE_H
