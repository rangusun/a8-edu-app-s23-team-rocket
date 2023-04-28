/**
 *  A8: An-Educational-App
 *
 *  @brief Backend for the firework test mode level
 *
 *  This is an implementation for TestModeModel.h
 *
 *  By Anna Madsen, Carlos Gonzalez, Carter Edginton, Rachel Nguyen, and Zander Ruiz
 *  for CS 3505 in Spring 2023
*/
#include "TestModeModel.h"

TestModeModel::TestModeModel() {}

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
        // user successfully matched the most recently generated firework specifications
        emit userWinOrLoss(true);

        winStreak++;
        emit winStreakChanged(winStreak);
    }
    else
    {
        // user did not match the most recently generated firework specifications
        emit userWinOrLoss(false);
    }
}

void TestModeModel::resetWinStreak()
{
    // The win streak should only be reset if the user has not
    // fulfilled 3 client orders and passed the full testing level.
    if (winStreak < 3)
    {
        winStreak = 0;
        emit winStreakChanged(winStreak);
    }
}
