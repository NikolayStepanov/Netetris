#include "board.h"

Board::Board(size_t width, size_t height):
    m_width(width),
    m_height(height),
    m_numberCells(width * height)
{
    m_cells.reserve(m_numberCells);

    for(int index = 0; index < static_cast<int>(m_numberCells); index++)
    {
        size_t x = index % m_width;
        size_t y = index / m_width;

        m_cells.push_back(Cell(x, y, index));
    }
}

Board::~Board()
{
    m_cells.clear();
}

void Board::clear()
{
    for(auto &cell : m_cells)
    {
        cell.setCellState(CellState::EMPTY);
        cell.setCellAction(CellAction::EMPTY);
        cell.setFigureType(FigureType::EMPTY);
        cell.setColor("white");
    }
}

size_t Board::getWidth() const
{
    return m_width;
}

size_t Board::getHeight() const
{
    return  m_height;
}

size_t Board::getNumderCells() const
{
    return m_numberCells;
}

bool Board::setCellInformation(const CellInformation cellInformation)
{
    size_t index = cellInformation.index;

    m_cells[index].setCellState(cellInformation.cellState);
    m_cells[index].setCellAction(cellInformation.cellAction);
    m_cells[index].setFigureType(cellInformation.figureType);
    m_cells[index].setColor(cellInformation.color);

    return true;
}

void Board::clearCell(const size_t index)
{
    m_cells[index].setCellState(CellState::EMPTY);
    m_cells[index].setCellAction(CellAction::EMPTY);
    m_cells[index].setFigureType(FigureType::EMPTY);
    m_cells[index].setColor("white");
}

CellInformation Board::getCellInformation(const size_t index) const
{
    Cell cell = m_cells.at(index);
    CellInformation cellInformation;

    cellInformation.coordinate.setX(cell.getX());
    cellInformation.coordinate.setY(cell.getY());
    cellInformation.index = cell.getIndex();
    cellInformation.cellState = cell.getCellState();
    cellInformation.cellAction = cell.getCellAction();
    cellInformation.figureType = cell.getFigureType();
    cellInformation.color = cell.getColor();

    return cellInformation;
}

QVector<CellInformation> Board::getAllCellInformation() const
{
    QVector<CellInformation> cellsInformation;
    for(auto cell : m_cells)
    {
        cellsInformation.push_back(getCellInformation(cell.getIndex()));
    }
    return cellsInformation;
}

QList<CellInformation> Board::getCellsInformation(const QList<size_t> cellIndices) const
{
    QList<CellInformation> cellsInformation;
    for(auto cellIndex : cellIndices)
    {
        cellsInformation.push_back(getCellInformation(cellIndex));
    }
    return cellsInformation;
}
