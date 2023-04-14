#ifndef TUTORIALPAGE_H
#define TUTORIALPAGE_H

#include <QWidget>
#include <map>
#include "TutorialDialog.h"

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

    TutorialDialog starDialog;
    TutorialDialog blastDialog;
    TutorialDialog liftDialog;
    TutorialDialog otherDialog;

    map<QString, bool> dialogVisited;

    void CheckIfAllPagesVisited();
};

#endif // TUTORIALPAGE_H
