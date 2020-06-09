#ifndef FIGURES_H
#define FIGURES_H

#include <QVector>
#include <common.h>
#include <QColor>

const int number_figures= 7;
const int number_cells_for_figure = 16;

static QVector <QVector<size_t>> figures
{
    {5,6,7,9},  // L
    {4,5,6,7},  // I
    {5,6,7,11}, // J
    {5,6,9,10}, // O
    {5,6,10,11},// Z
    {6,7,9,10}, // S
    {5,6,7,10}  // T
};


struct Figure
{
    QVector<CellInformation> cellsInformation;
    FigureType type = EMPTY;
    QColor color = Qt::white;
};

#endif // FIGURES_H
