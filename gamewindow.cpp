#include <QPainter>
#include "gamewindow.h"
#include "ui_gamewindow.h"

gamewindow::gamewindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gamewindow)
{
    ui->setupUi(this);
    ui->errorLabel->setVisible(false); //manually set error message invisible - no way in Qt Creator proper
}

gamewindow::~gamewindow()
{
    delete ui;
}

//initGameBoard - initializes the gameboard with the passed parameters
void gamewindow::initGame(int size, bool isCon)
{
    game = gameBoard(size, isCon);
    locations = new int[size];
}

//drawGame - draws the gameboard on the widget
void gamewindow::drawBoard()
{

}

//pickPeg - checks the state of the game, and then either makes a move or stores the picked peg for future use.
void gamewindow::pickPeg(int peg)
{
    ui->errorLabel->setVisible(false);

    if(secondPhase)
    {
        if(!game.moveDisc(firstPeg,peg))
        {
            ui->errorLabel->setVisible(true);
        }

        moves++;
        ui->moveCounter->setText(QString("Moves: %1").arg(moves));

        //after move check if the game is won
        if(game.gameIsWon())
            {
                ui->infoLabel->setText(QString("Congratulations! You won in %1 moves!").arg(moves));

                //disable UI buttons for moving
                ui->peg1Button->setEnabled(false);
                ui->peg2Button->setEnabled(false);
                ui->peg3Button->setEnabled(false);

                return;
            }

        secondPhase= false;
        ui->infoLabel->setText("Which disc would you like to move?");
    }
    else
    {
        firstPeg = peg;
        secondPhase=true;

        ui->infoLabel->setText("Which peg would you like to move the disc to?");
    }

}

//drawBoard -
void gamewindow::on_peg1Button_clicked()
{
    pickPeg(0); //start at 0 for the sake of less ugly code
}

void gamewindow::on_peg2Button_clicked()
{
    pickPeg(1);
}

void gamewindow::on_peg3Button_clicked()
{
    pickPeg(2);
}

void gamewindow::on_returnButton_clicked()
{
    delete [] locations; //deallocate dynamic memory
    close();
}
