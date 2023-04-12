#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include "Model.h"
#include <QTimer>

#include <QMovie>
#include <QPropertyAnimation>
#include <QSize>

QT_BEGIN_NAMESPACE
namespace Ui { class View; }
QT_END_NAMESPACE

/**
 * @brief The view portion of an MVC design for A5: QT Simon Game.
 *
 * This class handles all UI logic for a Simon Says game. After pressing a "start game" button,
 * The player is presented with two buttons that will light up in a specific sequence,
 * and the player is expected to press the buttons and replicate that sequence. If the player
 * successfully replicates the sequence, the sequence will be repeated with an additional step and
 * the player will replicate the longer sequence, and the game repeats until the player makes a mistake.
 * If the player loses, a message will display on the screen to notify them and they will have the
 * option to start again. The player will see a score to represent the number of complete turns.
 *
 * As an additonal feature, two animated characters from the Pokemon franchise display above
 * the buttons. These Pokemon show the player's project in a fun way, changing form as the
 * player presses the buttons more and more.
 *
 *
 * This project was created by Anna Madsen and Rachel Nguyen for CS 3505 in Spring of 2023
 */

class View : public QMainWindow
{
    Q_OBJECT

public:
    View(QWidget *parent = nullptr);
    ~View();

private:
    Ui::View *ui;

    Model model;

    QMovie *pkmOne;
    QMovie *pkmTwo;

    // Keeps track of the red pokemon's "levels" to evolve using button clicks.
    int redButtonClicks = 0;

    // Keeps track of the blue pokemon's "levels" to evolve using button clicks.
    int blueButtonClicks = 0;

    /**
     * @brief Helper method to disable the color buttons.
     */
    void disableColorButtons();

    /**
     * @brief Helper method to enable the color buttons.
     */
    void enableColorButtons();

    /**
     * @brief Lights up the red button to show the user a move in a sequence.
     */
    void lightRedButton();

    /**
     * @brief Return the button back to its original state.
     */
    void unlightRedButton();

    /**
     * @brief Lights up the blue button to show the user a move in a sequence.
     */
    void lightBlueButton();

    /**
     * @brief Return the button back to its original state.
     */
    void unlightBlueButton();

    /**
     * @brief initiate the player's next turn after a successful sequence completion.
     */
    void startPlayerTurn();

    /**
     * @brief Notifies the player failing their turn.
     */
    void playerFailed();

public slots:
    /**
     * @brief Recieves a signal to start the game.
     */
    void startGame();

    /**
     * @brief Receives a signal to display the sequence of moves to the user.
     */
    void displaySequence(const vector<Model::ButtonColor>);

    /**
     * @brief Receives a signal when the player has completed their turn successfully
     */
    void playerSequenceComplete();

    /**
     * @brief display the player's progress
     * @param the player's progress through their turn, as a percent from 0 to 100
     */
    void updateProgressBar(int progress);

    /**
     * @brief Show the given score on the screen.
     * @param score
     */
    void displayScore(int score);

    /**
     * @brief Ends the game on a failed player move.
     */
    void endGame();

    /**
     * @brief Reacts to button presses by counting them and eventually "evolving"
     * a Charmander on the screen
     */
    void redButtonAnimate();

    /**
     * @brief Reacts to button presses by counting them and eventually "evolving"
     * a Charmander on the screen
     */
    void blueButtonAnimate();


};
#endif // VIEW_H
