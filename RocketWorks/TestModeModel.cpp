#include "TestModeModel.h"

TestModeModel::TestModeModel()
{

}

void TestModeModel::generateFireworkSpecifications()
{
    QString shapeSpec;
    QString colorSpec;
    QString soundSpec;
    int shellDiameterSpec;

    // Randomly generate a firework shape specification.
    int randomSpec = rand() % 4;
    shapeSpec = shapeOptions[randomSpec];
    fireworkSpec.setShape(shapeSpec);

    // Randomly generate a firework color specification.
    randomSpec = rand() % 7;
    colorSpec = colorOptions[randomSpec];
    fireworkSpec.setColor(colorSpec);

    // Randomly generate a firework sound specification.
    randomSpec = rand() % 3;
    soundSpec = soundOptions[randomSpec];
    fireworkSpec.setSound(soundSpec);

    // Randomly generate a firework shell diameter specification.
    shellDiameterSpec = rand() % (shellDiameterMax - shellDiameterMin) + shellDiameterMin ;
    fireworkSpec.setShellDiameter(shellDiameterSpec);


    emit specificationsGenerated(shapeSpec, colorSpec, soundSpec, shellDiameterSpec);
}

void TestModeModel::checkUserSelections(FireworkProperties& userSelections)
{
    if(userSelections == fireworkSpec)
    {
        emit userWinOrLoss(true);

        winStreak++;
        emit winStreakChanged(winStreak);
    }
    else
    {
        emit userWinOrLoss(false);

        winStreak = 0;
        emit winStreakChanged(winStreak);
    }
}

void TestModeModel::resetWinStreak()
{
    winStreak = 0;
    emit winStreakChanged(winStreak);
}
