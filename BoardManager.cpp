#include "BoardManager.h"

#include <QPoint>
#include <QRect>
#include <QModelIndex>

#include "board.h"

void BoardManager::initialize(Bootstrapper *boostrap)
{

}

BoardManager::BoardManager():board(nullptr)
{
    //board = new Board(24,24);
    board = new Board(14,14);
}

BoardManager::~BoardManager()
{
    if(board!=nullptr)
    {
        delete board;
        board = nullptr;
    }
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

void BoardManager::clearAllBoard()
{
    board->clear();

    emit updateAllBoard();
}

size_t BoardManager::getWidthBoard() const
{
    return board->getWidth();
}

size_t BoardManager::getHeightBoard() const
{
    return  board->getHeight();
}

size_t BoardManager::getNumderCells() const
{
    return  board->getNumderCells();
}

QPair<size_t, size_t> BoardManager::getSizeBoard() const
{
    QPair<size_t,size_t> sizeBoard(getWidthBoard(), getHeightBoard());
    return  sizeBoard;
}

void BoardManager::setCellInformation(const CellInformation cellInformation)
{
    if(areCellIndexValid(cellInformation.index))
    {
        board->setCellInformation(cellInformation);
        emit updateCell(cellInformation.index);
    }
}

void BoardManager::clearRow(size_t row)
{
    QVector<size_t> cellIndices;
    int columns = board->getWidth();
    cellIndices.reserve(columns);

    for(int column = 0; column < columns; column++)
    {
        size_t indexCell = columns *  row + column;
        board->clearCell(indexCell);
    }

    emit updateRow(row);
}

void BoardManager::clearColumn(size_t column)
{
    QVector<size_t> cellIndices;
    int rows = board->getHeight();
    int columns = board->getWidth();

    cellIndices.reserve(rows);

    for(int row = 0; row < rows; row++)
    {
        size_t indexCell = columns * row + column;
        board->clearCell(indexCell);
    }

    emit updateColumn(column);
}

void BoardManager::clearCell(size_t cellIndex)
{
    if(areCellIndexValid(cellIndex))
    {
        board->clearCell(cellIndex);
        emit updateCell(cellIndex);
    }
}

CellInformation BoardManager::getCellInformation(size_t cellIndex) const
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

QList<CellInformation> BoardManager::getCellsInformation(QList<size_t> cellIndices) const
{
    bool validIndices = true;
    for(auto index:cellIndices)
    {
        if(areCellIndexValid(index))
        {
            validIndices = false;
            break;
        }
    }

    return validIndices?board->getCellsInformation(cellIndices):QList<CellInformation>();
}

QList<CellInformation> BoardManager::getCellsInformation(QList<QPoint> cellPoints) const
{
    QList<size_t> cellIndices;

    for(auto cellPoint : cellPoints)
    {
        cellIndices.push_back(cellIndex(cellPoint));
    }
    return getCellsInformation(cellIndices);
}

bool BoardManager::areCellIndexValid(size_t cellIndex) const
{
    QPoint coordinate = cellCoordinateFromIndex(cellIndex);
    return areCellcoordinateValid(coordinate);
}

bool BoardManager::areCellcoordinateValid(const QPoint &coordinate) const
{
    return QRect(0, 0, getWidthBoard(), getHeightBoard()).contains(coordinate);
}

QVector<QPoint> BoardManager::cellsCoordinatesFromIndices(QVector<size_t> cellIndices) const
{
    QVector<QPoint> cellsCoordinates;

    for(auto cellIndex : cellIndices)
    {
        cellsCoordinates.push_back(cellCoordinateFromIndex(cellIndex));
    }
    return cellsCoordinates;
}

QPoint BoardManager::cellCoordinateFromIndex(size_t cellIndex) const
{
    return {static_cast<int>(cellIndex % getWidthBoard()),
                static_cast<int>(cellIndex / getWidthBoard())};
}

size_t BoardManager::cellIndex(const QPoint &coordinate) const
{
    if(areCellcoordinateValid(coordinate))
    {
        return size_t(coordinate.y() * getWidthBoard() + coordinate.x());
    }
    return UINT64_MAX;
}

size_t BoardManager::cellIndex(const QModelIndex &index) const
{
    return cellIndex(QPoint(index.column(), index.row()));
}
