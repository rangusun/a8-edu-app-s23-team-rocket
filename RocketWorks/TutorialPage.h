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
    explicit TutorialPage(QWidget *parent = nullptr);
    ~TutorialPage();

private:
    Ui::TutorialPage *ui;

    TutorialDialog componentDialog;

    map<RocketComponent, bool> dialogsVisited;

    void CheckIfAllPagesVisited();
};

#endif // TUTORIALPAGE_H
