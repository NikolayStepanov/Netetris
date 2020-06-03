#include "board.h"

Board::Board(size_t width, size_t height):
    m_width(width),m_height(height),m_size(width*height)
{
    m_cells.reserve(sizeof(Cell)*m_size);
    for(int i=0;i<static_cast<int>(m_size);i++)
    {
        m_cells.push_back(Cell());
    }
}

Board::~Board()
{
    m_cells.clear();
}
