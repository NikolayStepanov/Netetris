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
    horizontalLineMaxFigures =(boardManager->getHeightBoard()*0.2);

    boardAllInformationCurrent.reserve(boardManager->getNumderCells());
    nextFigure = m_generator->randomFigure();
    currentFigure = m_generator->randomFigure();
    nextStep();
}

void GameLogicManager::nextStep()
{
    timerDownMove->stop();

    boardAllInformationCurrent = boardManager->getAllCellsInformation();
    if(deleteWholeLines())
    {
        boardAllInformationCurrent = boardManager->getAllCellsInformation();
    }

    currentFigure = nextFigure;
    nextFigure = m_generator->randomFigure();
    timerDownMove->start();
}

bool GameLogicManager::deleteWholeLines()
{
    bool b_delete=false;
    int columns = boardManager->getWidthBoard();
    int rows = boardManager->getHeightBoard();
    for(int row=horizontalLineMaxFigures; row<rows; row++)
    {
        bool deleteRow = true;
        for(int column=0; column<columns; column++)
        {
            if(boardAllInformationCurrent[columns*row+column].type==EMPTY)
            {
                deleteRow=false;
                break;
            }
        }

        if(deleteRow)
        {
            boardManager->clearRow(row);
            b_delete=true;
        }
    }
    return b_delete;
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

QVector<CellInformation> GameLogicManager::getCellsInformationBoxCurrentFigure(QPoint coordinateOffset)
{
    QVector<CellInformation> cellsInformationBox;
    cellsInformationBox.reserve(number_cells_for_figure);

    for(auto cellInfFigure: currentFigure.cellsInformation)
    {
        QPoint point(cellInfFigure.coordinates.x(),cellInfFigure.coordinates.y());

        point.setX(point.x()+coordinateOffset.x());
        point.setY(point.y()+coordinateOffset.y());


        size_t indexBoard = boardManager->cellIndex(point);

        if(indexBoard!=SIZE_MAX)
        {
            cellsInformationBox.push_back(boardAllInformationCurrent.value(indexBoard));
        }
        else
        {
            CellInformation cellInformation;
            cellInformation.coordinates.setX(point.x());
            cellInformation.coordinates.setY(point.y());
            cellsInformationBox.push_back(cellInformation);
        }
    }

    return cellsInformationBox;
}

void GameLogicManager::actionFigure(FigureAction actionFigure )
{
    switch (actionFigure)
    {
    case ROTATE:
    {
        rotationFigure();
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
    QVector<CellInformation> cellsInformationBox;
    cellsInformationBox.reserve(number_cells_for_figure);

    cellsInformationBox=getCellsInformationBoxCurrentFigure(coordinateOffset);

    if(canPutFigureInBox(currentFigure,cellsInformationBox))
    {
        deleteFigureinInBoard(currentFigure);
        putFigureInBoard(currentFigure,cellsInformationBox);
        isMovedFigure = true;
    }
    return isMovedFigure;
}

bool GameLogicManager::rotationFigure()
{
    bool isRotateFigure = false;

    QVector<CellInformation> cellsInformationBox;
    cellsInformationBox.reserve(number_cells_for_figure);

    FigureBox rotationFigureBox;

    if(currentFigure.type==O_TETRAMINO)
    {
        return isRotateFigure;
    }

    cellsInformationBox=getCellsInformationBoxCurrentFigure(QPoint(0,0));

    rotationFigureBox = rotationFigureInBox(currentFigure);

    if(canPutFigureInBox(rotationFigureBox,cellsInformationBox))
    {
        deleteFigureinInBoard(currentFigure);
        currentFigure = rotationFigureBox;
        putFigureInBoard(currentFigure,cellsInformationBox);
        isRotateFigure = true;
    }
    return isRotateFigure;
}

FigureBox GameLogicManager::rotationFigureInBox(FigureBox figureBox)
{
    FigureBox rotationFigureBox = figureBox;
    QPoint centerRotation = figureBox.cellsInformation[index_center_of_rotation_figure].coordinates;

    QVector<size_t> newIndcesNonEmptyCell;
    newIndcesNonEmptyCell.reserve(number_non_empty_cell);

    QVector<CellInformation> cellsInformationNonEmptyCell;
    cellsInformationNonEmptyCell.reserve(number_non_empty_cell);

    for(auto indexCell:figureBox.indicesNonEmptyCell)
    {
        rotationFigureBox.cellsInformation[indexCell].type=EMPTY;
        rotationFigureBox.cellsInformation[indexCell].color="white";
    }

    for(auto indexCell:figureBox.indicesNonEmptyCell)
    {
        cellsInformationNonEmptyCell.push_back(figureBox.cellsInformation[indexCell]);
    }
    do{
        for(auto &cellInf:cellsInformationNonEmptyCell)
        {
            int x = cellInf.coordinates.y()-centerRotation.y();
            int y = cellInf.coordinates.x()-centerRotation.x();
            cellInf.coordinates.setX(centerRotation.x()-x);
            cellInf.coordinates.setY(centerRotation.y()+y);
        }
    }while (!cellsContainedInBox(cellsInformationNonEmptyCell,figureBox));

    for(auto cellsInf:cellsInformationNonEmptyCell)
    {
        size_t indexNonEmptyCell =0;
        for(auto &cellInformationBox:rotationFigureBox.cellsInformation)
        {
            if(cellInformationBox.coordinates  == cellsInf.coordinates )
            {
                cellInformationBox.color = cellsInf.color;
                cellInformationBox.type = cellsInf.type;
                newIndcesNonEmptyCell.push_back(indexNonEmptyCell);
                break;
            }
            indexNonEmptyCell++;
        }
    }
    rotationFigureBox.indicesNonEmptyCell = newIndcesNonEmptyCell;
    return rotationFigureBox;
}

bool GameLogicManager::cellsContainedInBox(QVector<CellInformation> cellsInformation, FigureBox figureBox) const
{
    int minX = figureBox.cellsInformation[0].coordinates.x();
    int minY = figureBox.cellsInformation[0].coordinates.y();
    int maxX = figureBox.cellsInformation[15].coordinates.x();
    int maxY = figureBox.cellsInformation[15].coordinates.y();

    for(auto cellInf:cellsInformation)
    {
        if(minX>cellInf.coordinates.x() ||
                maxX<cellInf.coordinates.x() ||
                minY>cellInf.coordinates.y() ||
                maxY<cellInf.coordinates.y())
        {
            return false;
        }
    }
    return true;
}
