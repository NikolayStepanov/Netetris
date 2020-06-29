#ifndef COMMON_H
#define COMMON_H

#include <cstddef>
#include <cstdint>
#include <QString>
#include <QColor>
#include <QPoint>

#include "CellStateClass.h"
#include "CellActionClass.h"

typedef CellStateClass::Value CellState;
typedef CellActionClass::Value CellAction;

enum FigureAction
{
    FIX,
    ROTATE,
    MOVE_TOP,
    MOVE_DOWN,
    MOVE_RIGHT,
    MOVE_LEFT
};

enum class FigureType
{
    EMPTY = -1,
    L_TETRAMINO,
    I_TETRAMINO,
    J_TETRAMINO,
    O_TETRAMINO,
    Z_TETRAMINO,
    S_TETRAMINO,
    T_TETRAMINO
};

enum Color
{
    COLOR_WHITE = 0,
    COLOR_BLACK,
    COLOR_BLUE,
    COLOR_RED,
    COLOR_ORANGE,
    COLOR_PURPLE,
    COLOR_GRAY,
    COLOR_GREEN,
    COLOR_BROWN,
    COLOR_YELLOW,
    COLOR_CYAN,
    COLOR_MAGENTA
};

const int number_color = 12;

inline QString strColor(Color color)
{
    QString colorStr = "no";
    switch (color)
    {
    case COLOR_WHITE:
        colorStr = "white";
        break;
    case COLOR_BLACK:
        colorStr = "black";
        break;
    case COLOR_BLUE:
        colorStr = "blue";
        break;
    case COLOR_RED:
        colorStr = "red";
        break;
    case COLOR_ORANGE:
        colorStr = "#ffa500";
        break;
    case COLOR_PURPLE:
        colorStr = "#800080";
        break;
    case COLOR_GRAY:
        colorStr = "gray";
        break;
    case COLOR_GREEN:
        colorStr = "green";
        break;
    case COLOR_BROWN:
        colorStr = "#964b00";
        break;
    case COLOR_YELLOW:
        colorStr = "yellow";
        break;
    case COLOR_CYAN:
        colorStr = "cyan";
        break;
    case COLOR_MAGENTA:
        colorStr = "magenta";
        break;

    }
    return colorStr;
}

struct CellInformation
{
    CellInformation() = default;
    CellInformation(CellInformation const &) = default;
    CellInformation(CellInformation &&) = default;
    CellInformation& operator= (const CellInformation &) = default;

    void becomeEmptyCell()
    {
        cellState = CellState::EMPTY;
        cellAction = CellAction::EMPTY;
        figureType = FigureType::EMPTY;
        color = "white";
    }

    QPoint coordinate = QPoint(-1,-1);

    size_t index = UINT64_MAX;

    QString color = "white";

    CellState cellState = CellState::EMPTY;
    CellAction cellAction = CellAction::EMPTY;
    FigureType figureType = FigureType::EMPTY;
};
#endif // COMMON_H
