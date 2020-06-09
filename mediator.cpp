#include "mediator.h"

#include <bootstrapper.h>

Mediator * Mediator::p_instance = nullptr;


Mediator::Mediator(QObject *parent):
    QObject(parent), boardManager(nullptr)
{
    bootstrapper = new Bootstrapper();
}

Mediator *Mediator::getInstance()
{
    if(!p_instance)
        p_instance = new Mediator();
    return p_instance;
}

void Mediator::initialize()
{
    bootstrapper->initialize();
    boardManager = bootstrapper->getBoardManager();
}

Mediator::~Mediator()
{
    delete boardManager;
    delete bootstrapper;
}

int Mediator::getRowCountBoard()
{
    return getHeightBoard();
}

int Mediator::getColumnCountBoard()
{
    return getWidthBoard();
}

size_t Mediator::getWidthBoard()
{
    return boardManager->getWidthBoard();
}

size_t Mediator::getHeightBoard()
{
    return boardManager->getHeightBoard();
}

CellInformation Mediator::getCellInformation(const QModelIndex &index)
{
    size_t indexCell = boardManager->cellIndex(index);

    return boardManager->getCellInformation(indexCell);
}
