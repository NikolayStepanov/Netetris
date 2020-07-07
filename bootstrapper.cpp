#include "bootstrapper.h"

Bootstrapper::Bootstrapper()
{
    generator = new Generator;
    boardManager = new BoardManager;
    gameLogicManager = new GameLogicManager;
    analystManager = new AnalystManager;
}

void Bootstrapper::initialize()
{
    generator->initialize(this);
    boardManager->initialize(this);
    gameLogicManager->initialize(this);
    analystManager->initialize(this);
}

Bootstrapper::~Bootstrapper()
{
    delete generator;
    delete boardManager;
    delete gameLogicManager;
    delete analystManager;
}

BoardManager *Bootstrapper::getBoardManager()
{
    return boardManager;
}

GameLogicManager *Bootstrapper::getLogicManager()
{
    return gameLogicManager;
}

Generator *Bootstrapper::getGenerator()
{
    return generator;
}

AnalystManager *Bootstrapper::getAnalystManager()
{
    return analystManager;
}
