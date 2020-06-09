#ifndef BOARD_H
#define BOARD_H

#include <QVector>
#include <QMap>

#include <cell.h>

class Board
{
public:
    Board(size_t width,size_t height);
    ~Board();

    //get
    size_t getWidth();
    size_t getHeight();

    //set
    bool setCellInformation(const CellInformation cellInformation);

    //get CellInformation
    CellInformation getCellInformation(const size_t index) const;
    QVector<CellInformation> getAllCellInformation() const;
    QList<CellInformation> getCellsInformation(const QList<size_t> cellIndices) const;

private:
    QVector<Cell> m_cells;
    size_t m_width;
    size_t m_height;
    size_t m_numberCells;
};

#endif // BOARD_H
