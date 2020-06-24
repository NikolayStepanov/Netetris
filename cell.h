#ifndef CELL_H
#define CELL_H

#include "common.h"

class Cell
{
public:
    Cell();
    Cell(size_t index);
    Cell(size_t x, size_t y, size_t index);

    bool isEmpty();

    //set
    void setX(size_t x);
    void setY(size_t y);
    void setIndex(size_t index);
    void setColor(QString color);
    void setType(FigureType type);

    //get
    size_t getX();
    size_t getY();
    size_t getIndex();
    QString getColor();
    FigureType getType();

private:
    size_t m_x;
    size_t m_y;
    size_t m_index;

    QString m_color;
    FigureType m_type;
};

#endif // CELL_H
