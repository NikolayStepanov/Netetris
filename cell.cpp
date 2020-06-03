#include "cell.h"

Cell::Cell():
    m_empty(false),m_x(UINT64_MAX),m_y(UINT64_MAX),
    m_index(UINT64_MAX),m_color("white"),m_type(EMPTY)
{

}

Cell::~Cell()
{

}

bool Cell::isEmpty()
{
    return  m_empty;
}
