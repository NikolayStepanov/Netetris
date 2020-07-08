#ifndef BOOTSTRAPPER_H
#define BOOTSTRAPPER_H

#include "BoardManager.h"
#include "GameLogicManager.h"
#include "Generator.h"
#include "AnalystManager.h"

class Bootstrapper
{
public:
    Bootstrapper();
    ~Bootstrapper();

    void initialize();

    //get
    BoardManager *getBoardManager();
    GameLogicManager *getLogicManager();
    Generator *getGenerator();
    AnalystManager *getAnalystManager();

private:
    BoardManager * boardManager;
    GameLogicManager * gameLogicManager;
    Generator * generator;
    AnalystManager * analystManager;
};

#endif // BOOTSTRAPPER_H
