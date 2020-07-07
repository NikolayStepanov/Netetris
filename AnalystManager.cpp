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

int AnalystManager::howManyLinesDeletion(FigureBox figurePosition) const
{
    QList<int> rowNumbers;
    QList<int> colNumbers;
    QVector<QPoint> cellsNonEmptyFigure;
    //cellsNonEmptyFigure.reserve(NUMBER_NON_EMPTY_CELL);

    int countLinesDeletion = 0;

    for(auto indexCell : figurePosition.indicesNonEmptyCell)
    {
        QPoint cellCoordinate = figurePosition.cellsInformation[indexCell].coordinate;

        cellsNonEmptyFigure.push_back(cellCoordinate);

        if(!colNumbers.contains(cellCoordinate.x()))
        {
            colNumbers.push_back(cellCoordinate.x());
        }

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
            if(cellsNonEmptyFigure.contains(cellInf.coordinate))
            {
                continue;
            }
            else
            {
                if(cellInf.figureType == FigureType::EMPTY)
                {
                    b_rowDel = false;
                    break;
                }
            }
        }

        if(b_rowDel)
        {
            countLinesDeletion++;
        }
    }


    for(auto col : colNumbers)
    {
        bool b_colDel = true;
        QVector<CellInformation> cellInfCol;
        int sizeCol = m_pGameLogicManager->getMaxXY().y() - m_pGameLogicManager->getMinXY().y() + 1;
        cellInfCol.reserve(sizeCol);

        cellInfCol =  m_pGameLogicManager->getColumnBoardCurrentCellInformation(col);

        for(auto cellInf : cellInfCol)
        {
            if(cellsNonEmptyFigure.contains(cellInf.coordinate))
            {
                continue;
            }
            else
            {
                if(cellInf.figureType == FigureType::EMPTY)
                {
                    b_colDel = false;
                    break;
                }
            }
        }
        if(b_colDel)
        {
            countLinesDeletion++;
        }
    }

    return countLinesDeletion;
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

    weightFinalPosition = howManyLinesDeletion(figurePosition) * WEIGHT_LINE;
    weightFinalPosition = weightFinalPosition +  howManyNeighborsFigure(figurePosition) * WEIGHT_NEIGHBOR;

    return weightFinalPosition;
}
