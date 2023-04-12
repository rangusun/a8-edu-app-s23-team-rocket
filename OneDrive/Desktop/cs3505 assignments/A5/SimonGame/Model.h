#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <vector>

using std::vector;

/**
 * @brief The model portion of a MVC design for A5: QT Simon Game
 *
 * This class models a Simon Says game where the computer creates a growing sequence of colors that the player
 * must replicate by pushing buttons. The model is in charge of tracking the color sequence, validating player
 * moves, and adding to the color sequence. The model sends signals to the view to notify it of increases of score,
 * player success, player failure, etc..
 *
 * By Anna Madsen and Rachel Nguyen for CS 3505 in Spring 2023
 */
class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);

    /**
     * @brief an enum of available button colors that can be in the game sequence
     */
    enum ButtonColor {red, blue};

    /**
     * @brief Initiate the CPUs next turn in the game.
     */
    void addMoveToCPUSequence();

public slots:
    /**
     * @brief Once the start button has been pressed, start the game.
     */
    void startPressed();

    /**
     * @brief React to the red button being pressed. Check whether the player is correctly progressing along a sequence of button presses.
     */
    void validateRedPress();

    /**
     * @brief React to the blue button being pressed. Check whether the player is correctly progressing along a sequence of button presses.
     */
    void validateBluePress();

signals:
    /**
     * @brief Sends out a signal to indicate the game has been started.
     */
    void gameStarted();

    /**
     * @brief Sends out a signal to have the CPU show its sequence.
     */
    void startCPUSequence(const vector<Model::ButtonColor>);

    /**
     * @brief Sends out a signal that the player has correctly guessed all moves for this turn.
     */
    void playerFinishedSequence();

    /**
     * @brief Sends out a signal that player has incorrectly guessed the move of this sequence.
     */
    void playerFailed();

    /**
     * @brief Notify the view that the player pushed a correct button
     * @param the player's progress as a percent from 0 to 100
     */
    void playerSuccessfulMove(int progress);

    /**
     * @brief notify the view that the player's score changed.
     * @param score
     */
    void playerScoreChanged(int score);

private:
    /**
     * @brief Keeps track of which step the player is at of the current sequence.
     */
    unsigned int buttonPressCount = 0;

    /**
     * @brief Keeps track of the player's score so far
     */
    int score = 0;

    /**
     * @brief A sequence of buttons to press stored so far.
     */
    vector<ButtonColor> buttonSequence;

    /**
     * @brief A private helper method that generates a random move for the CPU's sequence.
     * @return A character representing the button that will be the next move in the sequence.
     */
    ButtonColor generateRandomMove();

};

#endif // MODEL_H
