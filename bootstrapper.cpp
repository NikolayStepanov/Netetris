#include "bootstrapper.h"

Bootstrapper::Bootstrapper()
{
    boardManager = new BoardManager;
    gameLogicManager = new GameLogicManager;
}

void Bootstrapper::initialize()
{
    boardManager->initialize(this);
    gameLogicManager->initialize(this);
}

BoardManager *Bootstrapper::getBoardManager()
{
    return boardManager;
}

GameLogicManager *Bootstrapper::getLogicManager()
{
    return gameLogicManager;
}
