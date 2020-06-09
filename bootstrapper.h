#ifndef BOOTSTRAPPER_H
#define BOOTSTRAPPER_H

#include <BoardManager.h>
#include <GameLogicManager.h>

class Bootstrapper
{
public:
    Bootstrapper();
    void initialize();
    //get
    BoardManager *getBoardManager();
    GameLogicManager *getLogicManager();

private:
    BoardManager * boardManager;
    GameLogicManager * gameLogicManager;
};

#endif // BOOTSTRAPPER_H
