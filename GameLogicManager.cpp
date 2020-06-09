#include "GameLogicManager.h"
#include <bootstrapper.h>
GameLogicManager::GameLogicManager(QObject *parent) : QObject(parent)
{

}

void GameLogicManager::initialize(Bootstrapper *boostrap)
{
   boardManager = boostrap->getBoardManager();
}
