#include "mediator.h"

#include <QPoint>
#include <QModelIndex>

#include "bootstrapper.h"

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
    gameLogicManager = bootstrapper->getLogicManager();

    //BoardManager
    connect(boardManager, &BoardManager::updateCell, this, &Mediator::slotUpdateCell);
    connect(boardManager, &BoardManager::updateRow, this, &Mediator::slotUpdateRow);
    connect(boardManager, &BoardManager::updateColumn, this, &Mediator::slotUpdateColumn);

    //GameLogicManager
    connect(gameLogicManager, &GameLogicManager::updateNextFigure, this, &Mediator::slotUbdateNextFigure);
    connect(gameLogicManager, &GameLogicManager::updateNumberLines, this, &Mediator::slotUpdateNumberLines);
}

Mediator::~Mediator()
{
    if(bootstrapper != nullptr)
    {
        delete bootstrapper;
        bootstrapper = nullptr;
    }
}

int Mediator::getRowCountBoard() const
{
    return getHeightBoard();
}

int Mediator::getColumnCountBoard() const
{
    return getWidthBoard();
}

size_t Mediator::getWidthBoard() const
{
    return boardManager->getWidthBoard();
}

size_t Mediator::getHeightBoard() const
{
    return boardManager->getHeightBoard();
}

CellInformation Mediator::getCellInformation(const QModelIndex &index)
{
    size_t indexCell = boardManager->cellIndex(index);

    return boardManager->getCellInformation(indexCell);
}

QPoint Mediator::getPointForIndex(size_t index)
{
    return boardManager->cellCoordinatesFromIndex(index);
}

CellInformation Mediator::getCellInformationNextFigure(const QModelIndex &index)
{
    QPoint coordinat = QPoint(index.column(), index.row());
    return gameLogicManager->getCellNextFigure(coordinat);

}

void Mediator::actionFigure(FigureAction actionFigure)
{
    gameLogicManager->actionFigure(actionFigure);
}

void Mediator::newGame()
{
    boardManager->createBoard(24, 24);
    gameLogicManager->newGame();
    gameLogicManager->startGame();
}

int Mediator::getNumberLines()
{
    return gameLogicManager->getNumberLines();
}

QPoint Mediator::minCoordinateBorder() const
{
    return gameLogicManager->getMinXY();
}

QPoint Mediator::maxCoordinateBorder() const
{
    return gameLogicManager->getMaxXY();
}

bool Mediator::isBorder(QPoint coordinate) const
{
    return gameLogicManager->isCoordinateBorder(coordinate);
}

void Mediator::slotUpdateCell(size_t index)
{
    emit updateCell(index);
}

void Mediator::slotUpdateRow(size_t row)
{
    emit updateRow(row);
}

void Mediator::slotUpdateColumn(size_t column)
{
    emit updateColumn(column);
}

void Mediator::slotUbdateNextFigure()
{
    emit updateNextFigure();
}

void Mediator::slotUpdateNumberLines(int lines)
{
    emit updateNumberLines(lines);
}
