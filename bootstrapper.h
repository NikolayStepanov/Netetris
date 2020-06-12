#ifndef BOOTSTRAPPER_H
#define BOOTSTRAPPER_H

#include <BoardManager.h>
#include <GameLogicManager.h>
#include <Generator.h>

class Bootstrapper
{
public:
    Bootstrapper();
    void initialize();
    //get
    BoardManager *getBoardManager();
    GameLogicManager *getLogicManager();
    Generator *getGenerator();

private:
    BoardManager * boardManager;
    GameLogicManager * gameLogicManager;
    Generator * m_generator;
};

#endif // BOOTSTRAPPER_H
