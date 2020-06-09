#include "board.h"

Board::Board(size_t width, size_t height):
    m_width(width),m_height(height),m_numberCells(width*height)
{
    m_cells.reserve(sizeof(Cell)*m_numberCells);
    for(int i=0;i<static_cast<int>(m_numberCells);i++)
    {
        m_cells.push_back(Cell());
    }
}

Board::~Board()
{
    m_cells.clear();
}

size_t Board::getWidth()
{
    return m_width;
}

size_t Board::getHeight()
{
    return  m_height;
}

bool Board::setCellInformation(const CellInformation cellInformation)
{
    size_t index = cellInformation.index;
    m_cells.value(index).setType(cellInformation.type);
    m_cells.value(index).setColor(cellInformation.color);
    return true;
}

CellInformation Board::getCellInformation(const size_t index) const
{
    Cell cell = m_cells.at(index);
    CellInformation cellInformation;

    if(!cell.isEmpty())
    {
        cellInformation.x = cell.getX();
        cellInformation.y = cell.getY();
        cellInformation.index = cell.getIndex();
        cellInformation.type = cell.getType();
        cellInformation.color = cell.getColor();
    }

    return cellInformation;
}

QVector<CellInformation> Board::getAllCellInformation() const
{
    QVector<CellInformation> cellsInformation;
    for(auto cell:m_cells)
    {
        cellsInformation.push_back(getCellInformation(cell.getIndex()));
    }
    return cellsInformation;
}

QList<CellInformation> Board::getCellsInformation(const QList<size_t> cellIndices) const
{
    QList<CellInformation> cellsInformation;
    for(auto cellIndex:cellIndices)
    {
        cellsInformation.push_back(getCellInformation(cellIndex));
    }
    return cellsInformation;
}
