#include "GameLogicManager.h"
#include <QDebug>
#include <QPoint>

#include <bootstrapper.h>


GameLogicManager::GameLogicManager(QObject *parent) :
    QObject(parent),
    m_pBoardManager(nullptr),
    m_pGenerator(nullptr),
    m_numberLines(0),
    m_minXY(0,0),
    m_maxXY(0,0)
{

}

void GameLogicManager::initialize(Bootstrapper *boostrap)
{
    m_pBoardManager = boostrap->getBoardManager();
    m_pGenerator = boostrap->getGenerator();

    m_numberLines = 0;

    m_minXY.setX(SIZE_BOXING_BORDER);
    m_minXY.setY(SIZE_BOXING_BORDER);
    m_maxXY.setX(m_pBoardManager->getWidthBoard() - SIZE_BOXING_BORDER - 1);
    m_maxXY.setY(m_pBoardManager->getHeightBoard() - SIZE_BOXING_BORDER - 1);
}

void GameLogicManager::newGame()
{
    m_boardAllInformationCurrent.clear();
    m_pBoardManager->clearAllBoard();
    setNumberLines(0);

    m_boardAllInformationCurrent.reserve(m_pBoardManager->getNumderCells());
    m_nextFigure = m_pGenerator->randomFigure();
    nextStep();
}

void GameLogicManager::finishGame()
{
    emit gameOver();
}

bool GameLogicManager::endGame()
{
    bool b_endGame = true;

    int numberOfVerticalOffsets = m_maxXY.y() - m_minXY.y() + SIZE_BOXING_BORDER;
    int numberOfHorizontalOffsets = m_maxXY.x() - m_minXY.x() + SIZE_BOXING_BORDER;

    FigureBox figura = m_currentFigure;

    do{
        for(int xOffset = 1; xOffset <= numberOfHorizontalOffsets; xOffset++)
        {
            for(int yOffset = 1; yOffset <= numberOfVerticalOffsets; yOffset++)
            {
                QPoint coordinateOffset(xOffset, yOffset);

                QVector<CellInformation> cellsInformationBox  = getCellsInformationBoxFigure(figura, coordinateOffset);

                bool b_canPutFigureInBox = true;

                for(auto indexCell : figura.indicesNonEmptyCell)
                {
                    if(isCoordinateBorder(cellsInformationBox[indexCell].coordinate) ||
                            cellsInformationBox[indexCell].cellState != CellState::EMPTY)
                    {
                        b_canPutFigureInBox = false;
                        break;
                    }
                }

                if(b_canPutFigureInBox)
                {
                    b_endGame = false;

                    return b_endGame;
                }
            }
        }
        figura = rotationFigureInBox(figura);
    } while(m_currentFigure != figura);

    if(b_endGame)
    {
        qDebug()<<"game Over";
    }
    return b_endGame;
}

void GameLogicManager::startGame()
{

}

void GameLogicManager::stopGame()
{

}

void GameLogicManager::addLinesPoints()
{
    m_numberLines++;
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

   if(endGame())
   {
       finishGame();
   }
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
        return m_nextFigure.cellsInformation[coordinat.y() * 4 + coordinat.x()];
    }
    else
    {
        return CellInformation();
    };
}

bool GameLogicManager::deleteWholeLines()
{
    bool b_delete = false;

    if(deleteColumns())
    {
        b_delete = true;
    }
    if(deleteRows())
    {
        b_delete = true;
    }

    return b_delete;
}

bool GameLogicManager::deleteColumns()
{
    bool b_delete=false;

    int columns = m_pBoardManager->getWidthBoard();

    for(int column = m_minXY.x(); column <= m_maxXY.x(); column++)
    {
        bool deleteRow = true;
        for(int row = m_minXY.y(); row <= m_maxXY.y(); row++)
        {
            if(m_boardAllInformationCurrent[columns * row + column].cellState == CellState::EMPTY)
            {
                deleteRow = false;
                break;
            }
        }

        if(deleteRow)
        {
            m_pBoardManager->clearColumn(column);
            addLinesPoints();
            b_delete = true;
        }
    }

    return b_delete;
}

bool GameLogicManager::deleteRows()
{
    bool b_delete = false;

    int columns = m_pBoardManager->getWidthBoard();

    for(int row = m_minXY.y(); row <= m_maxXY.y(); row++)
    {
        bool deleteRow = true;
        for(int column = m_minXY.x(); column <= m_maxXY.x(); column++)
        {
            if(m_boardAllInformationCurrent[columns * row + column].cellState == CellState::EMPTY)
            {
                deleteRow = false;
                break;
            }
        }

        if(deleteRow)
        {
            m_pBoardManager->clearRow(row);
            addLinesPoints();
            b_delete = true;
        }
    }

    return b_delete;
}

bool GameLogicManager::canPutFigureInBox(FigureBox &figureBox, QVector<CellInformation> &cellInformationBox)
{
    for(auto index:figureBox.indicesNonEmptyCell)
    {
        CellInformation cellInformation = cellInformationBox[index];
        if(     cellInformation.coordinate.x() < 0 ||
                cellInformation.coordinate.x() >= (static_cast<int>(m_pBoardManager->getWidthBoard())) ||
                cellInformation.coordinate.y() >= (static_cast<int>(m_pBoardManager->getHeightBoard())) ||
                cellInformation.coordinate.y() < 0)
        {
            return false;
        }
    }

    return true;
}

void GameLogicManager::deleteFigureInBoard(FigureBox &currentFigure)
{
    for(auto index : currentFigure.indicesNonEmptyCell)
    {
        QPoint coordinateCell = currentFigure.cellsInformation[index].coordinate;

        CellInformation cellInformationPastCondition =
                m_boardAllInformationCurrent[m_pBoardManager->cellIndex(coordinateCell)];

        m_pBoardManager->setCellInformation(cellInformationPastCondition);
    }
}

void GameLogicManager::putFigureInBoard(FigureBox &currentFigure, QVector<CellInformation> &cellInformationBox)
{
    size_t indexCell = 0;

    for(auto & cellFigure : currentFigure.cellsInformation)
    {
        cellFigure.coordinate = cellInformationBox[indexCell].coordinate;
        cellFigure.index = cellInformationBox[indexCell].index;
        indexCell++;
    }

    for(auto indexCellFigure : currentFigure.indicesNonEmptyCell)
    {
        if(cellInformationBox[indexCellFigure].cellState != CellState::EMPTY)
        {
            CellInformation cellInforamation = currentFigure.cellsInformation[indexCellFigure];

            cellInforamation.cellAction = CellAction::OVERLAP;

            m_pBoardManager->setCellInformation(cellInforamation);
        }
        else
        {
            m_pBoardManager->setCellInformation(currentFigure.cellsInformation[indexCellFigure]);
        }
    }
}

QVector<CellInformation> GameLogicManager::getCellsInformationBoxCurrentFigure(QPoint coordinateOffset)
{
    QVector<CellInformation> cellsInformationBox;
    cellsInformationBox.reserve(NUMBER_CELLS_FOR_FIGURE);

    for(auto cellInfFigure : m_currentFigure.cellsInformation)
    {
        QPoint point(cellInfFigure.coordinate.x(), cellInfFigure.coordinate.y());

        point.setX(point.x() + coordinateOffset.x());
        point.setY(point.y() + coordinateOffset.y());


        size_t indexBoard = m_pBoardManager->cellIndex(point);

        if(indexBoard != SIZE_MAX)
        {
            cellsInformationBox.push_back(m_boardAllInformationCurrent.value(indexBoard));
        }
        else
        {
            CellInformation cellInformation;
            cellInformation.coordinate.setX(point.x());
            cellInformation.coordinate.setY(point.y());
            cellsInformationBox.push_back(cellInformation);
        }
    }

    return cellsInformationBox;
}

QVector<CellInformation> GameLogicManager::getCellsInformationBoxFigure(FigureBox figureBox, QPoint coordinateOffset)
{
    QVector<CellInformation> cellsInformationBox;
    cellsInformationBox.reserve(NUMBER_CELLS_FOR_FIGURE);

    for(auto cellInfFigure : figureBox.cellsInformation)
    {
        QPoint point(cellInfFigure.coordinate.x(), cellInfFigure.coordinate.y());

        point.setX(point.x() + coordinateOffset.x());
        point.setY(point.y() + coordinateOffset.y());


        size_t indexBoard = m_pBoardManager->cellIndex(point);

        if(indexBoard != SIZE_MAX)
        {
            cellsInformationBox.push_back(m_boardAllInformationCurrent.value(indexBoard));
        }
        else
        {
            CellInformation cellInformation;
            cellInformation.coordinate.setX(point.x());
            cellInformation.coordinate.setY(point.y());
            cellsInformationBox.push_back(cellInformation);
        }
    }

    return cellsInformationBox;
}

void GameLogicManager::actionFigure(FigureAction actionFigure )
{
    switch (actionFigure)
    {
    case FIX:
    {
        fixCurrentFigure();
        break;
    }
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
    cellsInformationBox.reserve(NUMBER_CELLS_FOR_FIGURE);

    cellsInformationBox = getCellsInformationBoxCurrentFigure(coordinateOffset);

    if(canPutFigureInBox(m_currentFigure, cellsInformationBox))
    {
        deleteFigureInBoard(m_currentFigure);
        putFigureInBoard(m_currentFigure, cellsInformationBox);
        isMovedFigure = true;
    }

    return isMovedFigure;
}

bool GameLogicManager::fixCurrentFigure()
{
    bool b_fixCurrent = canFixFigureOnBoard(m_currentFigure);

    if(b_fixCurrent)
    {
        for(auto indexNonEmptyCell : m_currentFigure.indicesNonEmptyCell)
        {
            CellInformation cellInformation = m_currentFigure.cellsInformation[indexNonEmptyCell];
            cellInformation.cellState = CellState::FIXED;
            m_pBoardManager->setCellInformation(cellInformation);
        }
        nextStep();
    }

    return b_fixCurrent;
}

bool GameLogicManager::canFixFigureOnBoard(FigureBox &figure) const
{
    bool b_canFix = true;

    for(auto indexNonEmptyCell : figure.indicesNonEmptyCell)
    {
        QPoint coordinateCell = figure.cellsInformation[indexNonEmptyCell].coordinate;

        CellInformation cellInfBoard = m_boardAllInformationCurrent[m_pBoardManager->cellIndex(coordinateCell)];

        if(cellInfBoard.cellState != CellState::EMPTY || coordinateCell.x() < m_minXY.x() || coordinateCell.x() > m_maxXY.x() ||
                coordinateCell.y() < m_minXY.y() || coordinateCell.y() > m_maxXY.y())
        {
            b_canFix = false;
            break;
        }
    }

    return b_canFix;
}

bool GameLogicManager::rotationFigure()
{
    bool isRotateFigure = false;

    QVector<CellInformation> cellsInformationBox;
    cellsInformationBox.reserve(NUMBER_CELLS_FOR_FIGURE);

    FigureBox rotationFigureBox;

    if(m_currentFigure.type == FigureType::O_TETRAMINO)
    {
        return isRotateFigure;
    }

    cellsInformationBox = getCellsInformationBoxCurrentFigure(QPoint(0,0));

    rotationFigureBox = rotationFigureInBox(m_currentFigure);

    if(canPutFigureInBox(rotationFigureBox, cellsInformationBox))
    {
        deleteFigureInBoard(m_currentFigure);
        m_currentFigure = rotationFigureBox;
        putFigureInBoard(m_currentFigure, cellsInformationBox);
        isRotateFigure = true;
    }

    return isRotateFigure;
}

FigureBox GameLogicManager::rotationFigureInBox(FigureBox figureBox)
{
    FigureBox rotationFigureBox = figureBox;
    QPoint centerRotation = figureBox.cellsInformation[INDEX_CENTER_OF_ROTATION_FIGURE].coordinate;

    QVector<size_t> newIndcesNonEmptyCell;
    newIndcesNonEmptyCell.reserve(NUMBER_NON_EMPTY_CELL);

    QVector<CellInformation> cellsInformationNonEmptyCell;
    cellsInformationNonEmptyCell.reserve(NUMBER_NON_EMPTY_CELL);

    for(auto indexCell:figureBox.indicesNonEmptyCell)
    {
        rotationFigureBox.cellsInformation[indexCell].becomeEmptyCell();
    }

    for(auto indexCell:figureBox.indicesNonEmptyCell)
    {
        cellsInformationNonEmptyCell.push_back(figureBox.cellsInformation[indexCell]);
    }

    do{
        for(auto &cellInf:cellsInformationNonEmptyCell)
        {
            int x = cellInf.coordinate.y() - centerRotation.y();
            int y = cellInf.coordinate.x() - centerRotation.x();
            cellInf.coordinate.setX(centerRotation.x() - x);
            cellInf.coordinate.setY(centerRotation.y() + y);
        }
    }while (!cellsContainedInBox(cellsInformationNonEmptyCell, figureBox));

    for(auto cellsInf : cellsInformationNonEmptyCell)
    {
        size_t indexNonEmptyCell = 0;

        for(auto &cellInformationBox:rotationFigureBox.cellsInformation)
        {
            if(cellInformationBox.coordinate == cellsInf.coordinate )
            {
                cellInformationBox.color = cellsInf.color;
                cellInformationBox.cellState = cellsInf.cellState;
                cellInformationBox.cellAction = cellsInf.cellAction;
                cellInformationBox.figureType = cellsInf.figureType;

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
    int minX = figureBox.cellsInformation[0].coordinate.x();
    int minY = figureBox.cellsInformation[0].coordinate.y();
    int maxX = figureBox.cellsInformation[15].coordinate.x();
    int maxY = figureBox.cellsInformation[15].coordinate.y();

    for(auto cellInf : cellsInformation)
    {
        if(minX > cellInf.coordinate.x() ||
                maxX < cellInf.coordinate.x() ||
                minY > cellInf.coordinate.y() ||
                maxY < cellInf.coordinate.y())
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

QPoint GameLogicManager::getMinXY() const
{
    return m_minXY;
}

QPoint GameLogicManager::getMaxXY() const
{
    return m_maxXY;
}

void GameLogicManager::setNumberLines(int numberLines)
{
    if(m_numberLines != numberLines)
    {
        m_numberLines = numberLines;
        emit updateNumberLines(m_numberLines);
    }
}

bool GameLogicManager::isCoordinateBorder(QPoint coordinate) const
{
    bool b_iscoordinateBorder = false;

    if(coordinate.x() < m_minXY.x() || coordinate.x() > m_maxXY.x() ||
            coordinate.y() < m_minXY.y() || coordinate.y() > m_maxXY.y())
    {
        b_iscoordinateBorder = true;
    }

    return b_iscoordinateBorder;
}
