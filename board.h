#ifndef BOARD_H
#define BOARD_H

#include <QVector>
#include <cell.h>

class Board
{
public:
    Board(size_t width,size_t height);
    ~Board();
private:
    QVector<Cell> m_cells;
    size_t m_width;
    size_t m_height;
    size_t m_size;

};

#endif // BOARD_H
