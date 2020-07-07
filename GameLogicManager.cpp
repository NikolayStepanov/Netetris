#include "GameLogicManager.h"

#include <QPoint>
#include <algorithm>

#include <bootstrapper.h>


GameLogicManager::GameLogicManager(QObject *parent) :
    QObject(parent),
    m_pBoardManager(nullptr),
    m_pGenerator(nullptr),
    m_pAnalystManager(nullptr),
    m_numberLines(0),
    m_minXY(0,0),
    m_maxXY(0,0),
    m_pHintDisplayTimer(nullptr)
{
    m_pHintDisplayTimer = new QTimer(this);

    connect(m_pHintDisplayTimer, SIGNAL(timeout()),this,SLOT(activateHint()));
}

void GameLogicManager::initialize(Bootstrapper *boostrap)
{
    m_pBoardManager = boostrap->getBoardManager();
    m_pGenerator = boostrap->getGenerator();
    m_pAnalystManager = boostrap->getAnalystManager();

    m_pHintDisplayTimer->setInterval(2000);
    m_numberLines = 0;

    m_minXY.setX(SIZE_BOXING_BORDER);
    m_minXY.setY(SIZE_BOXING_BORDER);
    m_maxXY.setX(m_pBoardManager->getWidthBoard() - SIZE_BOXING_BORDER - 1);
    m_maxXY.setY(m_pBoardManager->getHeightBoard() - SIZE_BOXING_BORDER - 1);
}

void GameLogicManager::hintWherePlaceFigure(FigureBox figure)
{
    int numberOfVerticalOffsets = m_maxXY.y() - m_minXY.y() + SIZE_BOXING_BORDER;
    int numberOfHorizontalOffsets = m_maxXY.x() - m_minXY.x() + SIZE_BOXING_BORDER;

    FigureBox copy_figura = figure;
    initialCoordinatesFigure(copy_figura);
    QList<FigureBox> positionsFigure;
    QList<int> positionWeights;

    do{
        for(int yOffset = 1; yOffset <= numberOfVerticalOffsets; yOffset++)
        {
            for(int xOffset = 1; xOffset <= numberOfHorizontalOffsets; xOffset++)
            {
                QPoint coordinateOffset(xOffset, yOffset);

                QVector<CellInformation> cellsInformationBox  =
                        getCellsInformationBoxFigure(copy_figura, coordinateOffset);

                bool b_canPutFigureInBox = true;

                for(auto indexCell : copy_figura.indicesNonEmptyCell)
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
                    FigureBox figurePosition = copy_figura;
                    for(int indexCell = 0; indexCell < NUMBER_CELLS_FOR_FIGURE; indexCell++)
                    {
                        CellInformation cellFigurePosition = figurePosition.cellsInformation[indexCell];
                        cellFigurePosition.coordinate = cellsInformationBox[indexCell].coordinate;
                        cellFigurePosition.index = cellsInformationBox[indexCell].index;
                        if( cellFigurePosition.figureType != FigureType::EMPTY)
                        {
                            cellFigurePosition.figureType = FigureType::EMPTY;
                            cellFigurePosition.cellAction = CellAction::PROMPT;
                        }
                        figurePosition.cellsInformation[indexCell] = cellFigurePosition;
                    }

                    positionsFigure.push_back(figurePosition);
                    int weightPosition = m_pAnalystManager->weightPositionFigure(figurePosition);
                    positionWeights.push_back(weightPosition);
                }
            }
        }
        copy_figura = rotationFigureInBox(copy_figura);
    } while(figure != copy_figura);

    int maxWeight = *std::max_element(positionWeights.begin(), positionWeights.end());

    m_bestPositionCellsInformation = positionsFigure[positionWeights.indexOf(maxWeight)];

    for(auto indexCell : m_bestPositionCellsInformation.indicesNonEmptyCell)
    {
        CellInformation cellInformation = m_bestPositionCellsInformation.cellsInformation[indexCell];
        cellInformation = m_pBoardManager->getCellInformation(cellInformation.index);
        cellInformation.cellAction = CellAction::PROMPT;
        m_pBoardManager->setCellInformation(cellInformation);
    }
}

void GameLogicManager::removeHint()
{
    if(m_bestPositionCellsInformation.type != FigureType::EMPTY)
    {
        for(auto indexCell : m_bestPositionCellsInformation.indicesNonEmptyCell)
        {

            int indexCellBoard = m_bestPositionCellsInformation.cellsInformation[indexCell].index;
            CellInformation cellInfBoard = m_pBoardManager->getCellInformation(indexCellBoard);
            if(cellInfBoard.cellAction == CellAction::PROMPT)
            {
                cellInfBoard.cellAction = CellAction::EMPTY;
                m_pBoardManager->setCellInformation(cellInfBoard);
            }
        }
    }
    FigureBox emptyFigureBox;
    m_bestPositionCellsInformation = emptyFigureBox;
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
    removeHint();
    m_boardAllInformationCurrent = m_pBoardManager->getAllCellsInformation();
    if(deleteWholeLines())
    {
        m_boardAllInformationCurrent = m_pBoardManager->getAllCellsInformation();
    }



    m_currentFigure = m_nextFigure;

    moveFigure();
    generateNextFigure();

    m_pHintDisplayTimer->start();

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
        int indexCellBoard = currentFigure.cellsInformation[index].index;

        CellInformation cellInformationPastCondition =
                m_boardAllInformationCurrent[m_pBoardManager->cellIndex(coordinateCell)];

        CellInformation cellInformationBoard = m_pBoardManager->getCellInformation(indexCellBoard);

        if(cellInformationBoard.cellAction == CellAction::PROMPT)
        {
            cellInformationPastCondition.cellAction = CellAction::PROMPT;
        }

        /*if(cellInformationBoard.cellAction == CellAction::OVERLAP)
        {
            cellInformationPastCondition.cellAction = CellAction::EMPTY;
        }*/

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
        CellInformation cellInformationFigure = currentFigure.cellsInformation[indexCellFigure];
        CellInformation cellInformationBoard = m_pBoardManager->getCellInformation(cellInformationFigure.index);

        if(cellInformationBox[indexCellFigure].cellState == CellState::FIXED)
        {
            cellInformationFigure.cellAction = CellAction::OVERLAP;
        }

        if(cellInformationBoard.cellAction == CellAction::PROMPT)
        {
            cellInformationFigure.cellAction = CellAction::PROMPT;
        }

        m_pBoardManager->setCellInformation(cellInformationFigure);
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
            //cellsInformationBox.push_back(m_pBoardManager->getCellInformation(indexBoard));
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
            //cellsInformationBox.push_back(m_pBoardManager->getCellInformation(indexBoard));
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

void GameLogicManager::activateHint()
{
    m_pHintDisplayTimer->stop();
    hintWherePlaceFigure(m_currentFigure);
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

QVector<CellInformation> GameLogicManager::getRowBoardCurrentCellInformation(int rowNumber)
{
    int columns = m_pBoardManager->getWidthBoard();
    QVector<CellInformation> rowCellInformation;
    //rowCellInformation.reserve(m_maxXY.x() - m_minXY.y() + 1);

    for(int col = m_minXY.x(); col <= m_maxXY.x(); col++)
    {
        rowCellInformation.push_back(m_boardAllInformationCurrent[columns * rowNumber + col]);
    }

    return  rowCellInformation;
}

QVector<CellInformation> GameLogicManager::getColumnBoardCurrentCellInformation(int columnNumber)
{
    int columns = m_pBoardManager->getWidthBoard();
    QVector<CellInformation> rowCellInformation;
    //rowCellInformation.reserve(m_maxXY.x() - m_minXY.y() + 1);


    for(int row = m_minXY.y(); row <= m_maxXY.y(); row++)
    {
        rowCellInformation.push_back(m_boardAllInformationCurrent[columns * row + columnNumber]);
    }

    return  rowCellInformation;
}

CellInformation GameLogicManager::getCellBoardCurrentCellInformation(QPoint coordinateCell)
{
    int columns = m_pBoardManager->getWidthBoard();
    return m_boardAllInformationCurrent[columns * coordinateCell.y() + coordinateCell.x()];
}

QVector<CellInformation> GameLogicManager::getBoardAllInformationCurrent()
{
    QVector<CellInformation> cellsInformation;
    for(auto cellInf : m_boardAllInformationCurrent)
    {
        cellsInformation.push_back(cellInf);
    }
    return cellsInformation;
}

void GameLogicManager::setNumberLines(int numberLines)
{
    if(m_numberLines != numberLines)
    {
        m_numberLines = numberLines;
        emit updateNumberLines(m_numberLines);
    }
}

void GameLogicManager::initialCoordinatesFigure(FigureBox &figure)
{
    int index = 0;
    for(int row = 0; row < SIZE_BOXING_BORDER; row++)
    {
        for(int col = 0; col < SIZE_BOXING_BORDER; col++)
        {
            QPoint coordinate(col, row);
            size_t indexCellBoard = m_pBoardManager->cellIndex(coordinate);
            figure.cellsInformation[index].index = indexCellBoard;
            figure.cellsInformation[index].coordinate = coordinate;
            index++;
        }
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
