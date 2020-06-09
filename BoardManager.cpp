#include "BoardManager.h"
#include <board.h>

#include <QPoint>
#include <QRect>
#include <QModelIndex>


void BoardManager::initialize(Bootstrapper *boostrap)
{

}

BoardManager::BoardManager():board(nullptr)
{
    board = new Board(30,16);
}

BoardManager::~BoardManager()
{
    delete board;
    board = nullptr;
}

bool BoardManager::createBoard(size_t width, size_t height)
{
    if(board==nullptr)
    {
        board = new Board(width,height);
    }
    else
    {
        delete board;
        board = new Board(width,height);
    }
    return true;
}

size_t BoardManager::getWidthBoard() const
{
    return board->getWidth();
}

size_t BoardManager::getHeightBoard() const
{
    return  board->getHeight();
}

QPair<size_t, size_t> BoardManager::getSizeBoard() const
{
    QPair<size_t,size_t> sizeBoard(getWidthBoard(),getHeightBoard());
    return  sizeBoard;
}

void BoardManager::setCellInformation(const CellInformation cellInformation)
{
    board->setCellInformation(cellInformation);
}

CellInformation BoardManager::getCellInformation(const size_t cellIndex) const
{
    CellInformation cellInformation;
    if(areCellIndexValid(cellIndex))
    {
        cellInformation = board->getCellInformation(cellIndex);
    }
    return cellInformation;
}

QVector<CellInformation> BoardManager::getAllCellsInformation() const
{
    return board->getAllCellInformation();
}

QList<CellInformation> BoardManager::getAllCellsInformation(const QList<size_t> cellIndices) const
{
    bool validIndices = true;
    for(auto index:cellIndices)
    {
        if(areCellIndexValid(index))
        {
            validIndices=false;
            break;
        }
    }

    return validIndices?board->getCellsInformation(cellIndices):QList<CellInformation>();
}

bool BoardManager::areCellIndexValid(const size_t cellIndex) const
{
    QPoint coordinates = cellCoordinatesFromIndex(cellIndex);
    return areCellCoordinatesValid(coordinates);
}

bool BoardManager::areCellCoordinatesValid(const QPoint &coordinates) const
{
    return QRect(0, 0, getWidthBoard(), getHeightBoard()).contains(coordinates);
}

QPoint BoardManager::cellCoordinatesFromIndex(const size_t cellIndex) const
{
    return {static_cast<int>(cellIndex % getWidthBoard()),
                static_cast<int>(cellIndex / getWidthBoard())};
}

size_t BoardManager::cellIndex(const QPoint &coordinates) const
{
    if(areCellCoordinatesValid(coordinates))
    {
        return size_t(coordinates.y() * getWidthBoard() + coordinates.x());
    }
    return UINT64_MAX;
}

size_t BoardManager::cellIndex(const QModelIndex &index) const
{
    return cellIndex(QPoint(index.column(),index.row()));
}
