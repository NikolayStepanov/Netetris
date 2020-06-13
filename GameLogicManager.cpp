#include "GameLogicManager.h"
#include <bootstrapper.h>
#include <QPoint>

GameLogicManager::GameLogicManager(QObject *parent) : QObject(parent),m_generator(nullptr)
{
    timerDownMove = new QTimer(this);
    timerDownMove->setInterval(1000);

    connect(timerDownMove,SIGNAL(timeout()),this,SLOT(actionFigure()));
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
        boardManager->clearCell(currentFigure.cellsInformation[index].index);
    }
}

void GameLogicManager::putFigureInBoard(FigureBox &currentFigure, QVector<CellInformation> &cellInformationBox)
{
    size_t indexCell = 0;

    for(auto & cellFigure:currentFigure.cellsInformation)
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

void GameLogicManager::actionFigure(FigureAction actionFigure )
{
    switch (actionFigure)
    {
    case ROTATE:
    {
        break;
    }
    case MOVE_DOWN:
    {
        bool b_moveDown = false;

        b_moveDown=moveFigure(QPoint(0,1));
        if(!b_moveDown)
        {
            nextStep();
        }
        break;
    }
    case MOVE_RIGHT:
    {
        moveFigure(QPoint(1,0));
        break;
    }
    case MOVE_LEFT:
    {
        moveFigure(QPoint(-1,0));
        break;
    }
    default:
    {
        break;
    }
    }
}

bool GameLogicManager::moveFigure(QPoint coordinateOffset)
{
    bool isMovedFigure = false;
    QVector<CellInformation> cellsInformationDownBox;
    cellsInformationDownBox.reserve(number_cells_for_figure);

    for(auto cellInfFigure: currentFigure.cellsInformation)
    {
        QPoint point(cellInfFigure.coordinates.x(),cellInfFigure.coordinates.y());

        point.setX(point.x()+coordinateOffset.x());
        point.setY(point.y()+coordinateOffset.y());


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
        isMovedFigure = true;
    }
    return isMovedFigure;
}

/*void GameLogicManager::downMoveFigure()
{
    QVector<CellInformation> cellsInformationDownBox;
    cellsInformationDownBox.reserve(number_cells_for_figure);


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
    //leftMoveFigure();
    //rightMoveFigure();
}

void GameLogicManager::rightMoveFigure()
{
    QVector<CellInformation> cellsInformationDownBox;
    cellsInformationDownBox.reserve(number_cells_for_figure);


    for(auto cellInfFigure: currentFigure.cellsInformation)
    {
        QPoint point(cellInfFigure.coordinates.x(),cellInfFigure.coordinates.y());
        point.setX(point.x()+1);

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
}

void GameLogicManager::leftMoveFigure()
{
    QVector<CellInformation> cellsInformationDownBox;
    cellsInformationDownBox.reserve(number_cells_for_figure);


    for(auto cellInfFigure: currentFigure.cellsInformation)
    {
        QPoint point(cellInfFigure.coordinates.x(),cellInfFigure.coordinates.y());
        point.setX(point.x()-1);

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
}*/
