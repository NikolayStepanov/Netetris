#include "GameLogicManager.h"
#include <bootstrapper.h>
#include <QPoint>

GameLogicManager::GameLogicManager(QObject *parent) : QObject(parent),
    m_pGenerator(nullptr),m_pBoardManager(nullptr),m_minXY(0,0),m_maxXY(0,0)
{

}

void GameLogicManager::initialize(Bootstrapper *boostrap)
{
    m_pBoardManager = boostrap->getBoardManager();
    m_pGenerator = boostrap->getGenerator();
    m_numberLines = 0;

    m_minXY.setX(size_boxing_border);
    m_minXY.setY(size_boxing_border);
    m_maxXY.setX(m_pBoardManager->getWidthBoard()-size_boxing_border-1);
    m_maxXY.setY(m_pBoardManager->getHeightBoard()-size_boxing_border-1);


    //m_currentFigure = m_pGenerator->randomFigure();

    /*indexHorizontalCenter = (boardManager->getWidthBoard()/2)-1;
    horizontalLineMaxFigures =(boardManager->getHeightBoard()*0.2);

    boardAllInformationCurrent.reserve(boardManager->getNumderCells());
    nextFigure = m_generator->randomFigure();
    currentFigure = m_generator->randomFigure();
    nextStep();*/
}

void GameLogicManager::newGame()
{
    m_boardAllInformationCurrent.reserve(m_pBoardManager->getNumderCells());
    m_nextFigure = m_pGenerator->randomFigure();
    //m_currentFigure = m_pGenerator->randomFigure();
    nextStep();
}

void GameLogicManager::gameOver()
{

}

void GameLogicManager::startGame()
{

}

void GameLogicManager::stopGame()
{

}

void GameLogicManager::addLinesPoints()
{
    m_numberLines=m_numberLines+1;
    emit updateNumberLines(m_numberLines);
}

void GameLogicManager::nextStep()
{
    m_boardAllInformationCurrent = m_pBoardManager->getAllCellsInformation();
    if(deleteWholeLines())
    {
        m_boardAllInformationCurrent = m_pBoardManager->getAllCellsInformation();
    }

    m_currentFigure = m_nextFigure;
    moveFigure();
    generateNextFigure();
}

void GameLogicManager::generateNextFigure()
{
    m_nextFigure = m_pGenerator->randomFigure();
    emit updateNextFigure();
}

CellInformation GameLogicManager::getCellNextFigure(QPoint coordinat)
{
    if(!m_nextFigure.cellsInformation.isEmpty())
    {
        return m_nextFigure.cellsInformation[coordinat.y()*4+coordinat.x()];
    }
    else
    {
        return CellInformation();
    };
}

bool GameLogicManager::deleteWholeLines()
{
    bool b_delete=false;
    if(deleteColumns() || deleteRows())
    {
        b_delete = true;
    }
    return b_delete;
}

bool GameLogicManager::deleteColumns()
{
    bool b_delete=false;

    int columns = m_pBoardManager->getWidthBoard();

    for(int column=m_minXY.x(); column<=m_maxXY.x(); column++)
    {
        bool deleteRow = true;
        for(int row=m_minXY.y(); row<=m_maxXY.y(); row++)
        {
            if(m_boardAllInformationCurrent[columns*row+column].type==EMPTY)
            {
                deleteRow=false;
                break;
            }
        }

        if(deleteRow)
        {
            m_pBoardManager->clearColumn(column);
            addLinesPoints();
            b_delete=true;
        }
    }
    return b_delete;
}

bool GameLogicManager::deleteRows()
{
    bool b_delete=false;

    int columns = m_pBoardManager->getWidthBoard();

    for(int row=m_minXY.y(); row<=m_maxXY.y(); row++)
    {
        bool deleteRow = true;
        for(int column=m_minXY.x(); column<=m_maxXY.x(); column++)
        {
            if(m_boardAllInformationCurrent[columns*row+column].type==EMPTY)
            {
                deleteRow=false;
                break;
            }
        }

        if(deleteRow)
        {
            m_pBoardManager->clearRow(row);
            addLinesPoints();
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
                cellInformation.coordinates.x()>=(static_cast<int>(m_pBoardManager->getWidthBoard())) ||
                cellInformation.coordinates.y()>=(static_cast<int>(m_pBoardManager->getHeightBoard())) ||
                cellInformation.coordinates.y()<0)
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
        m_pBoardManager->clearCell(currentFigure.cellsInformation[index].index);
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
        m_pBoardManager->setCellInformation(currentFigure.cellsInformation[indexCellFigure]);
    }
}

QVector<CellInformation> GameLogicManager::getCellsInformationBoxCurrentFigure(QPoint coordinateOffset)
{
    QVector<CellInformation> cellsInformationBox;
    cellsInformationBox.reserve(number_cells_for_figure);

    for(auto cellInfFigure: m_currentFigure.cellsInformation)
    {
        QPoint point(cellInfFigure.coordinates.x(),cellInfFigure.coordinates.y());

        point.setX(point.x()+coordinateOffset.x());
        point.setY(point.y()+coordinateOffset.y());


        size_t indexBoard = m_pBoardManager->cellIndex(point);

        if(indexBoard!=SIZE_MAX)
        {
            cellsInformationBox.push_back(m_boardAllInformationCurrent.value(indexBoard));
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
    case MOVE_TOP:
    {
        moveFigure(QPoint(0,-1));
        break;
    }
    case MOVE_DOWN:
    {
        moveFigure(QPoint(0,1));
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

    if(canPutFigureInBox(m_currentFigure,cellsInformationBox))
    {
        deleteFigureinInBoard(m_currentFigure);
        putFigureInBoard(m_currentFigure,cellsInformationBox);
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

    if(m_currentFigure.type==O_TETRAMINO)
    {
        return isRotateFigure;
    }

    cellsInformationBox=getCellsInformationBoxCurrentFigure(QPoint(0,0));

    rotationFigureBox = rotationFigureInBox(m_currentFigure);

    if(canPutFigureInBox(rotationFigureBox,cellsInformationBox))
    {
        deleteFigureinInBoard(m_currentFigure);
        m_currentFigure = rotationFigureBox;
        putFigureInBoard(m_currentFigure,cellsInformationBox);
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

bool GameLogicManager::getNumberLines() const
{
    return m_numberLines;
}
