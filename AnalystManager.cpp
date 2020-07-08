#include "AnalystManager.h"

#include <QVector>
#include <QSet>

#include <bootstrapper.h>

const int WEIGHT_LINE = 10;
const int WEIGHT_NEIGHBOR = 2;

AnalystManager::AnalystManager():
    m_pGameLogicManager(nullptr)
{

}

void AnalystManager::initialize(Bootstrapper *boostrap)
{
    m_pGameLogicManager = boostrap->getLogicManager();
}

int AnalystManager::howManyLinesCanDeleted(FigureBox figurePosition) const
{
    int countLinesDeleted = 0;

    int countRowDeleted = countRowCanDeleted(figurePosition);
    int countColumnDeleted = countColumnCanDeleted(figurePosition);

    countLinesDeleted = countRowDeleted + countColumnDeleted;

    return countLinesDeleted;
}

int AnalystManager::countRowCanDeleted(FigureBox figurePosition) const
{
    int coutRowDeleted = 0;

    QList<int> rowNumbers;
    QVector<QPoint> coodinateNonEmptyCellFigure;
    coodinateNonEmptyCellFigure.reserve(NUMBER_NON_EMPTY_CELL);

    for(auto indexCell : figurePosition.indicesNonEmptyCell)
    {
        QPoint cellCoordinate = figurePosition.cellsInformation[indexCell].coordinate;

        coodinateNonEmptyCellFigure.push_back(cellCoordinate);

        if(!rowNumbers.contains(cellCoordinate.y()))
        {
            rowNumbers.push_back(cellCoordinate.y());
        }
    }

    for(auto row : rowNumbers)
    {
        bool b_rowDel = true;
        QVector<CellInformation> cellInfRow;

        int sizeRow = m_pGameLogicManager->getMaxXY().x() - m_pGameLogicManager->getMinXY().x() + 1;
        cellInfRow.reserve(sizeRow);

        cellInfRow =  m_pGameLogicManager->getRowBoardCurrentCellInformation(row);

        for(auto cellInf : cellInfRow)
        {
            if(coodinateNonEmptyCellFigure.contains(cellInf.coordinate))
            {
                continue;
            }

            if(cellInf.figureType == FigureType::EMPTY)
            {
                b_rowDel = false;
                break;
            }
        }

        if(b_rowDel)
        {
            coutRowDeleted++;
        }
    }

    return coutRowDeleted;
}

int AnalystManager::countColumnCanDeleted(FigureBox figurePosition) const
{
    int coutColumnDeleted = 0;

    QList<int> columnNumbers;
    QVector<QPoint> coodinateNonEmptyCellFigure;
    coodinateNonEmptyCellFigure.reserve(NUMBER_NON_EMPTY_CELL);

    for(auto indexCell : figurePosition.indicesNonEmptyCell)
    {
        QPoint cellCoordinate = figurePosition.cellsInformation[indexCell].coordinate;

        coodinateNonEmptyCellFigure.push_back(cellCoordinate);

        if(!columnNumbers.contains(cellCoordinate.x()))
        {
            columnNumbers.push_back(cellCoordinate.x());
        }
    }

    for(auto col : columnNumbers)
    {
        bool b_colDel = true;

        QVector<CellInformation> cellInfColumn;
        int sizeCol = m_pGameLogicManager->getMaxXY().y() - m_pGameLogicManager->getMinXY().y() + 1;
        cellInfColumn.reserve(sizeCol);

        cellInfColumn =  m_pGameLogicManager->getColumnBoardCurrentCellInformation(col);

        for(auto cellInf : cellInfColumn)
        {
            if(coodinateNonEmptyCellFigure.contains(cellInf.coordinate))
            {
                continue;
            }

            if(cellInf.figureType == FigureType::EMPTY)
            {
                b_colDel = false;
                break;
            }

        }

        if(b_colDel)
        {
            coutColumnDeleted++;
        }
    }

    return coutColumnDeleted;
}

int AnalystManager::howManyNeighborsFigure(FigureBox figurePosition) const
{
    int countNeighbors = 0;

    QList<QPoint> cellCheckNeighbors;
    QList<QPoint> cellCoordinateNonEmptyCellFigure;

    QVector<CellInformation> boardInformation =
            m_pGameLogicManager->getBoardAllInformationCurrent();

    for(auto indexCell : figurePosition.indicesNonEmptyCell)
    {
        QPoint cellCoordinate = figurePosition.cellsInformation[indexCell].coordinate;
        cellCoordinateNonEmptyCellFigure.push_back(cellCoordinate);
    }

    for(auto cellCoordinate : cellCoordinateNonEmptyCellFigure)
    {
        QVector<QPoint> cellCoordinateNeighbors;
        cellCoordinateNeighbors.reserve(NUMBER_NEIGHBORS_CELL);

        cellCoordinateNeighbors.push_back(QPoint(cellCoordinate.x() - 1, cellCoordinate.y()));
        cellCoordinateNeighbors.push_back(QPoint(cellCoordinate.x() + 1, cellCoordinate.y()));
        cellCoordinateNeighbors.push_back(QPoint(cellCoordinate.x(), cellCoordinate.y() + 1));
        cellCoordinateNeighbors.push_back(QPoint(cellCoordinate.x(), cellCoordinate.y() - 1));

        for(auto cellCoordinate : cellCoordinateNeighbors)
        {
            if(cellCoordinateNonEmptyCellFigure.contains(cellCoordinate))
            {
                continue;
            }
            else
            {
                CellInformation cellInf = m_pGameLogicManager->getCellBoardCurrentCellInformation(cellCoordinate);
                if(cellInf.figureType == FigureType::EMPTY)
                {
                    continue;
                }
                else if(!cellCheckNeighbors.contains(cellCoordinate))
                {
                    cellCheckNeighbors.push_back(cellCoordinate);
                    countNeighbors++;
                }
            }
        }
    }

    return countNeighbors;
}

int AnalystManager::weightPositionFigure(FigureBox figurePosition) const
{
    int weightFinalPosition = 0;

    int countLinesDeleted = howManyLinesCanDeleted(figurePosition) * WEIGHT_LINE;
    int countNeighborsFigure = howManyNeighborsFigure(figurePosition) * WEIGHT_NEIGHBOR;

    weightFinalPosition = countLinesDeleted * WEIGHT_LINE +
            countNeighborsFigure * WEIGHT_NEIGHBOR;

    return weightFinalPosition;
}
