#include "View.h"
#include "ui_View.h"

/**
 * @brief View::View This class implements a View for A5: QT Simon Game described in View.h
 *
 *        Pokemon GIFS retrieved from: https://www.pokencyclopedia.info/en/index.php?id=sprites/gen5/ani_black-white
 *        Egg GIF retrieved from: https://www.pokencyclopedia.info/en/index.php?id=sprites/menu-icons/ico-a_old
 *
 * By Anna Madsen and Rachel Nguyen for CS 3505 in Spring 2023
 */
View::View(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::View)
{   
    ui->setupUi(this);

        // Get the 'click' signal from the startButton and tell the model to start a new game
        connect(ui->startButton,
                &QPushButton::clicked,
                &model,
                &Model::startPressed);
        // UI setup for starting a new game
        connect(&model,
                &Model::gameStarted,
                this,
                View::startGame);
        // Display the CPU's sequence choice
        connect(&model,
                &Model::startCPUSequence,
                this,
                &View::displaySequence);
        // Disable the red and blue buttons after the player's turn ended successfully.
        connect(&model,
                &Model::playerFinishedSequence,
                this,
                &View::playerSequenceComplete);
        // If the player clicks the red button, have the model check that this move
        // is the correct move in the sequence.
        connect(ui->redButton,
                &QPushButton::clicked,
                &model,
                &Model::validateRedPress);
        // If the player clicks the blue button, have the model check that this move
        // is the correct move in the sequence.
        connect(ui->blueButton,
                &QPushButton::clicked,
                &model,
                &Model::validateBluePress);

        // Update the UI to reflect a loss when the player loses, reenable the start button
        connect(&model,
                &Model::playerFailed,
                this,
                &View::endGame);

        // Display player progres through a turn
        connect(&model,
                &Model::playerSuccessfulMove,
                this,
                &View::updateProgressBar);

        // Display the player's score
        connect(&model,
                &Model::playerScoreChanged,
                this,
                &View::displayScore);

        // Animate Pokemon for special feature
        connect(ui->redButton,
                &QPushButton::clicked,
                this,
                &View::redButtonAnimate);
        connect(ui->blueButton,
                &QPushButton::clicked,
                this,
                &View::blueButtonAnimate);

        // Set the progress bar at 0 until the player makes their first move
        ui->turnProgressBar->setValue(0);

        // Disable the red and blue buttons until the player's first turn.
        ui->redButton->setEnabled(false);
        ui->blueButton->setEnabled(false);

        // Set the colors of the buttons.
        ui->redButton->setStyleSheet( QString("QPushButton {background-color: rgb(200,50,50);}"));
        ui->blueButton->setStyleSheet( QString("QPushButton {background-color: rgb(50,50,200);}"));

        // Starting the pokemon as eggs. Load in the gifs of the pokemon eggs.
        QMovie *pkmOne = new QMovie("../SimonGame/egg.gif");
        QMovie *pkmTwo = new QMovie("../SimonGame/egg.gif");

        // Resizing the sprite to a bigger size.
        QSize fixedEggSize(50,50);
        pkmOne->setScaledSize(fixedEggSize);
        pkmTwo->setScaledSize(fixedEggSize);

        // Start the animations of the gifs.
        ui->redPkmLabel->setMovie(pkmOne);
        ui->bluePkmLabel->setMovie(pkmTwo);
        pkmOne->start();
        pkmTwo->start();
}

void View::startGame()
{
    // Disable the start button for this game session.
    ui->loseLabel->setText("");
    ui->startButton->setEnabled(false);
    ui->turnProgressBar->setValue(0);

    // Set the pokemon back to their first-evolutions.
    pkmOne = new QMovie("../SimonGame/charmander.gif");
    pkmTwo = new QMovie("../SimonGame/squirtle.gif");

    ui->redPkmLabel->setMovie(pkmOne);
    ui->bluePkmLabel->setMovie(pkmTwo);
    pkmOne->start();
    pkmTwo->start();

    // Reset the pokemon's "levels" back to 0, since there have been no clicks for this game
    redButtonClicks = 0;
    blueButtonClicks = 0;
}

void View::updateProgressBar(int progress)
{
    // This slot will be triggered when the player makes a correct move.
    ui->turnProgressBar->setValue(progress);
}

void View::displaySequence(const vector<Model::ButtonColor> sequenceToDisplay)
{
    // Stop the animations for the CPU's turn.
    pkmOne->setPaused(true);
    pkmTwo->setPaused(true);

    // We set the delay at 800 to start, so there will be .8 seconds before the first move displays
    // This is so that the player has time to shift focus from pressing buttons to watching the next sequence.
    int delay = 800;
    // The increment tells us the delay between flashes, which will decrease as the sequence gets longer.
    int delayIncrement = 1000 - (sequenceToDisplay.size() * 50);
    if (delayIncrement < 300)
    {
        delayIncrement = 300;
    }

    // Display each move of the current sequence.
    for(Model::ButtonColor colorID : sequenceToDisplay)
    {
        // Look at the current move and flash the button of this move.
        switch(colorID)
        {
          case Model::red:
            // Change the button color to a lighter shade
            QTimer::singleShot(delay, this, &View::lightRedButton);
            // Change it back to its normal shade after a small interval
            QTimer::singleShot(delay+delayIncrement/3, this, &View::unlightRedButton);
            break;
          case Model::blue:
            // Change the button color to a lighter shade
            QTimer::singleShot(delay, this, &View::lightBlueButton);
            // Change it back to its normal shade after a small interval
            QTimer::singleShot(delay+delayIncrement/3, this, &View::unlightBlueButton);
            break;
        }

        // The delay passed to QTimer is cumulative since all singleShots in this loop will start
        // counting down nearly simultaneously.
        delay += delayIncrement;
    }

    // Speed up the Pokemon according to the number of buttons in the sequence
    pkmOne->setSpeed(100 + (sequenceToDisplay.size() - 3) * 15);
    pkmTwo->setSpeed(100 + (sequenceToDisplay.size() - 3) * 15);


    // It is now the player's turn, enable the color buttons.
    QTimer::singleShot(delay, this, &View::startPlayerTurn);
}

void View::lightBlueButton()
{
    ui->blueButton->setStyleSheet(QString("QPushButton {background-color: rgb(150,150,255);}"));
    update();
}

void View::unlightBlueButton()
{
    ui->blueButton->setStyleSheet(QString("QPushButton {background-color: rgb(50,50,200);} QPushButton:pressed {background-color: rgb(150,150,255);}"));
    update();
}

void View::lightRedButton()
{
    ui->redButton->setStyleSheet(QString("QPushButton {background-color: rgb(255,150,150);}"));
    update();
}

void View::unlightRedButton()
{
    ui->redButton->setStyleSheet( QString("QPushButton {background-color: rgb(200,50,50);} QPushButton:pressed {background-color: rgb(255,150,150);}"));
    update();
}

void View::disableColorButtons()
{
    ui->redButton->setEnabled(false);
    ui->blueButton->setEnabled(false);
}

void View::enableColorButtons()
{
    ui->redButton->setEnabled(true);
    ui->blueButton->setEnabled(true);
}

void View::playerSequenceComplete()
{
    // Turn off the buttons until the next sequence displays.
    disableColorButtons();
    // Tell the model to add a move to the sequence. The model will then
    // send a signal for the view to display the updated sequence.
    model.addMoveToCPUSequence();
}

void View::startPlayerTurn()
{
    // Resume the animation when it's the player's turn. A fun indication to tell the
    // player it is their turn.
    pkmOne->setPaused(false);
    pkmTwo->setPaused(false);

    enableColorButtons();
    ui->turnProgressBar->setValue(0);
}

void View::displayScore(int score)
{
    // From: https://stackoverflow.com/questions/3211771/how-to-convert-int-to-qstring
    QString scoreDisplay = QStringLiteral("Score: %1").arg(score);
    ui->scoreLabel->setText(scoreDisplay);
}

void View::redButtonAnimate()
{
    // The pokemon levels up by 1 with every click to the button that matches its color
    redButtonClicks++;

    // Once the player has clicked the button a certain number of times, the Pokemon
    // "evolves"
    if (redButtonClicks == 16)
    {
        pkmOne = new QMovie("../SimonGame/charmeleon.gif");

        ui->redPkmLabel->setMovie(pkmOne);
        pkmOne->start();
    }
    else if (redButtonClicks == 36)
    {
        pkmOne = new QMovie("../SimonGame/charizard.gif");

        ui->redPkmLabel->setMovie(pkmOne);
        pkmOne->start();
    }
}

void View::blueButtonAnimate()
{
    // The pokemon levels up by 1 with every click to the button that matches its color
    blueButtonClicks++;

    // Once the player has clicked the button a certain number of times, the Pokemon
    // "evolves"
    if (blueButtonClicks == 16)
    {
        pkmTwo = new QMovie("../SimonGame/wartortle.gif");

        ui->bluePkmLabel->setMovie(pkmTwo);
        pkmTwo->start();
    }
    else if (blueButtonClicks == 36)
    {
        pkmTwo = new QMovie("../SimonGame/blastoise.gif");

        ui->bluePkmLabel->setMovie(pkmTwo);
        pkmTwo->start();
    }

}

void View::endGame()
{
    // Notify the player of their loss
    ui->loseLabel->setText("You lose! Press Start to Try Again");

    disableColorButtons();

    // Reenable the start button to allow the player to try again
    ui->startButton->setEnabled(true);
}

View::~View()
{
    delete ui;
}

