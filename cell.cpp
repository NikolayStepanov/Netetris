#include "cell.h"

Cell::Cell():
    m_x(UINT64_MAX),m_y(UINT64_MAX),
    m_index(UINT64_MAX),m_color("white"),m_type(EMPTY)
{

}

Cell::Cell(size_t index):
    m_x(UINT64_MAX),m_y(UINT64_MAX),
    m_index(index),m_color("white"),m_type(EMPTY)
{

}

Cell::Cell(size_t x, size_t y, size_t index):m_x(x),m_y(y),
    m_index(index),m_color("white"),m_type(EMPTY)
{

}

Cell::~Cell()
{

}

bool Cell::isEmpty()
{
    return  m_type == EMPTY;
}

void Cell::setX(size_t x)
{
    m_x = x;
}

void Cell::setY(size_t y)
{
    m_y = y;
}

void Cell::setIndex(size_t index)
{
    m_index = index;
}

void Cell::setColor(QString color)
{
    m_color = color;
}

void Cell::setType(FigureType type)
{
    m_type = type;
}

size_t Cell::getX()
{
    return m_x;
}

size_t Cell::getY()
{
    return m_y;
}

size_t Cell::getIndex()
{
    return m_index;
}

QString Cell::getColor()
{
    return m_color;
}

FigureType Cell::getType()
{
    return m_type;
}
