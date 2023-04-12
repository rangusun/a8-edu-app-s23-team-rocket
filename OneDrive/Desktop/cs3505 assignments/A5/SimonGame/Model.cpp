#include "Model.h"
#include <random>

#include <iostream>

/**
 * @brief This is an implementation of a Model for A5: QT Simon Game described in Model.h
 *
 * By Anna Madsen and Rachel Nguyen for CS 3505 in Spring 2023
 */
Model::Model(QObject *parent)
{

}

void Model::startPressed()
{
    // Disable the start button
    emit gameStarted();

    // Reset the player's score
    score = 0;
    emit playerScoreChanged(score);

    // Clear the count of button presses from the player's last turn, if any
    buttonSequence.clear();
    buttonPressCount = 0;

    // Generate the first three moves for the player.
    buttonSequence.push_back(generateRandomMove());
    buttonSequence.push_back(generateRandomMove());
    buttonSequence.push_back(generateRandomMove());


    emit startCPUSequence(buttonSequence);
}

void Model::validateRedPress()
{
    if(buttonSequence.at(buttonPressCount) == Model::red)
    {
        emit playerSuccessfulMove(((buttonPressCount + 1) / (double)buttonSequence.size()) * 100);
        // The player made a correct guess. Check if they finished the sequence.
        if(buttonPressCount == buttonSequence.size() - 1)
        { 
            score++;

            emit playerScoreChanged(score);

            buttonPressCount = 0;

            emit playerFinishedSequence();
            return;
        }
    }
    else
    {
        // The player made an incorrect guess, notify the view.
        emit playerFailed();
    }

    buttonPressCount++;
}

void Model::validateBluePress()
{
    if(buttonSequence.at(buttonPressCount) == Model::blue)
    {
        emit playerSuccessfulMove(((buttonPressCount + 1) / (double)buttonSequence.size()) * 100);

        // The player made a correct guess. Check if they finished the sequence.
        if(buttonPressCount == buttonSequence.size() - 1)
        {
            score++;

            emit playerScoreChanged(score);

            buttonPressCount = 0;

            emit playerFinishedSequence();
            return;
        }
    }
    else
    {
        // The player made an incorrect guess, notify the view.
        emit playerFailed();
    }

    buttonPressCount++;
}

void Model::addMoveToCPUSequence()
{
    Model::ButtonColor nextMove = generateRandomMove();
    buttonSequence.push_back(nextMove);

    emit startCPUSequence(buttonSequence);
}

Model::ButtonColor Model::generateRandomMove()
{
    // Randomly generate a number and look at the last bit.
    // Getting a value that is either 0 or 1.
    int move = std::rand() & 1;

    if(move == 1)
    {
        // Red move
        return red;
    }
    else
    {
        // Blue move
        return blue;
    }
}


