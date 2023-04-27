#ifndef TESTMODEMODEL_H
#define TESTMODEMODEL_H

#include <QObject>
#include "FireworkProperties.h"

class TestModeModel : public QObject
{
    Q_OBJECT
public:
    TestModeModel();

    void generateFireworkSpecifications();
public slots:
    void checkUserSelections(FireworkProperties& userSelections);
    void resetWinStreak();

signals:
    void specificationsGenerated(QString shapeSpec, QString colorSpec, QString soundSpec, int shellDiameterSpec);
    void userWinOrLoss(bool win);
    void winStreakChanged(int streakCount);

private:
    FireworkProperties fireworkSpec;

    QString shapeOptions[4] = {"Circle", "Heart", "Smile", "Star"};
    QString colorOptions[8] = {"red", "orange", "yellow", "green", "blue", "purple", "pink", "white"};
    QString soundOptions[3] = {"Crackle", "Bang", "Whistle"};
    int shellDiameterMax = 13;
    int shellDiameterMin = 6;

    int winStreak = 0;
};

#endif // TESTMODEMODEL_H
