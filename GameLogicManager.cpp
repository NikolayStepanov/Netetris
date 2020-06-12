#include "GameLogicManager.h"
#include <bootstrapper.h>
#include <QPoint>

GameLogicManager::GameLogicManager(QObject *parent) : QObject(parent),m_generator(nullptr)
{
    timerDownMove = new QTimer(this);
    timerDownMove->setInterval(1000);

    connect(timerDownMove,SIGNAL(timeout()),this,SLOT(downMoveFigure()));
}

void GameLogicManager::initialize(Bootstrapper *boostrap)
{
    boardManager = boostrap->getBoardManager();
    m_generator = boostrap->getGenerator();
    indexHorizontalCenter = (boardManager->getWidthBoard()/2)-1;
    boardAllInformationCurrent.reserve(boardManager->getNumderCells());
    nextFigure = m_generator->randomFigure();
    currentFigure = m_generator->randomFigure();
    nextStep();
}

void GameLogicManager::nextStep()
{
    timerDownMove->stop();

    boardAllInformationCurrent = boardManager->getAllCellsInformation();
    currentFigure = nextFigure;
    nextFigure = m_generator->randomFigure();
    /*QVector<size_t> indexCellBox;

    int indexBox = 0;*/
    /*for(int y=0;y<4;y++)
    {
        for(size_t x=indexHorizontalCenter;x<(indexHorizontalCenter+4);x++)
        {
            size_t index= boardManager->cellIndex(QPoint(x,y));
            currentFigure.cellsInformation[indexBox].x=x;
            currentFigure.cellsInformation[indexBox].y=y;
            currentFigure.cellsInformation[indexBox].index =index;
        }
    }*/
    timerDownMove->start();
}

bool GameLogicManager::canPutFigureInBox(FigureBox &figureBox, QVector<CellInformation> &cellInformationBox)
{
    for(auto index:figureBox.indicesNonEmptyCell)
    {
        CellInformation cellInformation = cellInformationBox[index];
        if( cellInformation.type!=EMPTY ||
                cellInformation.coordinates.x()<0 ||
                cellInformation.coordinates.x()>=(static_cast<int>(boardManager->getWidthBoard())) ||
                cellInformation.coordinates.y()>=(static_cast<int>(boardManager->getHeightBoard())))
        {
            return false;
        }
    }
    return true;
}

void GameLogicManager::deleteFigureinInBoard(FigureBox &currentFigure)
{
    for(auto index:currentFigure.indicesNonEmptyCell)
    {
        CellInformation cellInformation;
        cellInformation.coordinates = currentFigure.cellsInformation[index].coordinates;
        boardManager->setCellInformation(cellInformation);
    }
}

void GameLogicManager::putFigureInBoard(FigureBox &currentFigure, QVector<CellInformation> &cellInformationBox)
{
    size_t indexCell = 0;

    for(auto cellFigure:currentFigure.cellsInformation)
    {
        cellFigure.coordinates = cellInformationBox[indexCell].coordinates;
        cellFigure.index = cellInformationBox[indexCell].index;
        indexCell++;
    }

    for(auto indexCellFigure:currentFigure.indicesNonEmptyCell)
    {
        boardManager->setCellInformation(currentFigure.cellsInformation[indexCellFigure]);
    }
}

void GameLogicManager::downMoveFigure()
{
    QVector<size_t> indexCellDownBox(number_cells_for_figure);
    QVector<CellInformation> cellsInformationDownBox(number_cells_for_figure);


    for(auto cellInfFigure: currentFigure.cellsInformation)
    {
        QPoint point(cellInfFigure.coordinates.x(),cellInfFigure.coordinates.y());
        point.setY(point.y()+1);

        size_t indexBoard = boardManager->cellIndex(point);

        if(indexBoard!=SIZE_MAX)
        {
            cellsInformationDownBox.push_back(boardAllInformationCurrent.value(indexBoard));
        }
        else
        {
            CellInformation cellInformation;
            cellInformation.coordinates.setX(point.x());
            cellInformation.coordinates.setY(point.y());
            cellsInformationDownBox.push_back(cellInformation);
        }
    }

    if(canPutFigureInBox(currentFigure,cellsInformationDownBox))
    {
        deleteFigureinInBoard(currentFigure);
        putFigureInBoard(currentFigure,cellsInformationDownBox);
    }
    else{
        nextStep();
    }

    /*bool canInsertFigure = true;
    for(auto indexCellFigure:figures[currentFigure.type])
    {
        if(cellsInformationDownBox.value(indexCellFigure).type!=EMPTY
                && cellsInformationDownBox.value(indexCellFigure).index==UINT64_MAX)
        {
            canInsertFigure = false;
            break;
        }
    }
    if(canInsertFigure)
    {
        for(auto indexCellFigure:figures[currentFigure.type])
        {
            CellInformation cellInfFigure = cellsInformationFigure.value(indexCellFigure);
            boardManager->clearCell(cellInfFigure.index);

            cellInfFigure.x = cellsInformationDownBox.value(indexCellFigure).x;
            cellInfFigure.y = cellsInformationDownBox.value(indexCellFigure).y;
            cellInfFigure.index = cellsInformationDownBox.value(indexCellFigure).index;

            cellsInformationFigure.value(indexCellFigure)= cellsInformationDownBox.value(indexCellFigure).x;
            cellsInformationFigure.value(indexCellFigure)=cellsInformationDownBox.value(indexCellFigure).y;
            cellsInformationFigure.value(indexCellFigure)=cellsInformationDownBox.value(indexCellFigure).index;

            boardManager->setCellInformation(cellInfFigure);

            for(int i=0;i<16;i++)
            {
                currentFigure.cellsInformation[i].x = cellsInformationDownBox.value(i).x;
                currentFigure.cellsInformation[i].y = cellsInformationDownBox.value(i).y;
                currentFigure.cellsInformation[i].index = cellsInformationDownBox.value(i).index;
            }
        }
    }
    else(nextStep()); */
}
