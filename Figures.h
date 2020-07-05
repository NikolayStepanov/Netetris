#ifndef FIGURES_H
#define FIGURES_H

#include <QVector>
#include <QColor>

#include "common.h"

const int SIZE_BOXING_BORDER = 4;
const int NUMBER_FIGURES = 7;
const int NUMBER_CELLS_FOR_FIGURE = 16;
const int NUMBER_NON_EMPTY_CELL = 4;
const int INDEX_CENTER_OF_ROTATION_FIGURE = 6;

static QVector <QVector<size_t>> FIGURES
{
    {5,6,7,9},  // L
    {4,5,6,7},  // I
    {5,6,7,11}, // J
    {5,6,9,10}, // O
    {5,6,10,11},// Z
    {6,7,9,10}, // S
    {5,6,7,10}  // T
};

struct FigureBox
{
    FigureBox()
    {
        cellsInformation.reserve(NUMBER_CELLS_FOR_FIGURE);
        indicesNonEmptyCell.reserve(NUMBER_NON_EMPTY_CELL);
    }

    CellInformation getCellInformation(size_t index) const
    {
        return cellsInformation.value(index);
    }

    void shiftCoordinates(QPoint coordinateOffset)
    {
        for(auto cellInfFigure : cellsInformation)
        {
            QPoint point(cellInfFigure.coordinate.x(), cellInfFigure.coordinate.y());

            point.setX(point.x() + coordinateOffset.x());
            point.setY(point.y() + coordinateOffset.y());
        }
    }

    bool operator== (const FigureBox &figureBox) const
    {
        return (this->cellsInformation == figureBox.cellsInformation);
    }

    bool operator!= (const FigureBox &figureBox) const
    {
        return !(*this == figureBox);
    }

    QVector<size_t> indicesNonEmptyCell;
    QVector<CellInformation> cellsInformation;
    FigureType type = FigureType::EMPTY;
    QColor color = Qt::white;
};

#endif // FIGURES_H
