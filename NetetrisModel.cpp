#include "NetetrisModel.h"
#include "mediator.h"

NetetrisModel::NetetrisModel(QObject *parent)
{
    mediator = Mediator::getInstance();
}

void NetetrisModel::newGame()
{
    mediator->newGame();
}

void NetetrisModel::startGame()
{

}

void NetetrisModel::stopGame()
{

}

void NetetrisModel::quitGame()
{

}

void NetetrisModel::rotate()
{
    mediator->actionFigure(FigureAction::ROTATE);
}

void NetetrisModel::moveDown()
{
    mediator->actionFigure(FigureAction::MOVE_DOWN);
}

void NetetrisModel::moveLeft()
{
    mediator->actionFigure(FigureAction::MOVE_LEFT);
}

void NetetrisModel::moveRight()
{
    mediator->actionFigure(FigureAction::MOVE_RIGHT);
}
