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
    boardAllInformationСurrent.reserve(boardManager->getNumderCells());
    nextFigure = m_generator->randomFigure();
    currentFigure = m_generator->randomFigure();
    nextStep();
}

void GameLogicManager::nextStep()
{
    timerDownMove->stop();

    boardAllInformationСurrent = boardManager->getAllCellsInformation();
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
        if(cellInformationBox[index].type!=EMPTY && cellInformationBox[index].index==SIZE_MAX)
        {
            return false;
        }
    }
    return true;
}

void GameLogicManager::putFigureInBoard(FigureBox &currentFigure, QVector<CellInformation> &cellInformation)
{
    size_t indexCell = 0;

    for(auto cellFigure:currentFigure.cellsInformation)
    {
        cellFigure.x = cellInformation[indexCell].x;
        cellFigure.y = cellInformation[indexCell].y;
        cellFigure.index = cellInformation[indexCell].index;
        indexCell++;
    }

    for(auto indexCell:currentFigure.indicesNonEmptyCell)
    {
       boardManager->setCellInformation(currentFigure.cellsInformation[indexCell]);
    }
}

void GameLogicManager::downMoveFigure()
{
    QVector<size_t> indexCellDownBox(number_cells_for_figure);

    for(auto cellInfFigure: currentFigure.cellsInformation)
    {
        indexCellDownBox.push_back(
                    boardManager->cellIndex(QPoint(cellInfFigure.y+1,cellInfFigure.x)));
    }

    QVector<CellInformation> cellsInformationDownBox(number_cells_for_figure);

    for(auto indexCell:indexCellDownBox)
    {
        if(indexCell==SIZE_MAX)
        {
            cellsInformationDownBox.push_back(CellInformation());
        }
        else{
            cellsInformationDownBox.push_back(boardAllInformationСurrent.value(indexCell));
        }
    }

    if(canPutFigureInBox(currentFigure,cellsInformationDownBox))
    {
        putFigureInBoard(currentFigure,cellsInformationDownBox);
    }
    else{

    }

    bool canInsertFigure = true;
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

            /*cellsInformationFigure.value(indexCellFigure)= cellsInformationDownBox.value(indexCellFigure).x;
            cellsInformationFigure.value(indexCellFigure)=cellsInformationDownBox.value(indexCellFigure).y;
            cellsInformationFigure.value(indexCellFigure)=cellsInformationDownBox.value(indexCellFigure).index;*/

            boardManager->setCellInformation(cellInfFigure);

            for(int i=0;i<16;i++)
            {
                currentFigure.cellsInformation[i].x = cellsInformationDownBox.value(i).x;
                currentFigure.cellsInformation[i].y = cellsInformationDownBox.value(i).y;
                currentFigure.cellsInformation[i].index = cellsInformationDownBox.value(i).index;
            }
        }
    }
    else(nextStep());
}
