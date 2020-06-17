#include "bootstrapper.h"

Bootstrapper::Bootstrapper()
{
    m_generator = new Generator;
    boardManager = new BoardManager;
    gameLogicManager = new GameLogicManager;
}

void Bootstrapper::initialize()
{
    m_generator->initialize(this);
    boardManager->initialize(this);
    gameLogicManager->initialize(this);
}

Bootstrapper::~Bootstrapper()
{
    delete m_generator;
    delete boardManager;
    delete gameLogicManager;
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
    return m_generator;
}
