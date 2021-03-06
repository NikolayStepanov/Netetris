#include "Generator.h"

#include <QTime>

#include <bootstrapper.h>
#include "Figures.h"

QString Generator::randomColor()
{
    Color color = static_cast<Color>(qrand() % (number_color - 2) + 2);

    return strColor(color);
}

FigureBox Generator::randomFigure()
{
    QString color = randomColor();
    FigureType typeFigure = static_cast<FigureType>(qrand() % NUMBER_FIGURES);

    FigureBox figureRandBox;

    figureRandBox.cellsInformation = emptyBox4x4ForFigure();
    figureRandBox.color = QColor(color);
    figureRandBox.type = typeFigure;
    figureRandBox.indicesNonEmptyCell = FIGURES[static_cast<int>(typeFigure)];

    for(auto index:figureRandBox.indicesNonEmptyCell)
    {
        figureRandBox.cellsInformation[index].figureType = typeFigure;
        figureRandBox.cellsInformation[index].color = color;
        figureRandBox.cellsInformation[index].cellState = CellState::NOT_FIXED;
    }

    return figureRandBox;
}

QVector<CellInformation> Generator::emptyBox4x4ForFigure()
{
    QVector<CellInformation> boxFigure;
    boxFigure.reserve(NUMBER_CELLS_FOR_FIGURE);

    for(int i = 0; i < NUMBER_CELLS_FOR_FIGURE; i++)
    {
        boxFigure.push_back(CellInformation());
    }

    int index = 0;
    int xStart = 0;

    for(int y = 0; y < SIZE_BOXING_BORDER; y++)
    {
        for(int x = xStart; x < (xStart + SIZE_BOXING_BORDER); x++)
        {
            boxFigure[index].coordinate.setX(x);
            boxFigure[index].coordinate.setY(y);
            index++;
        }
    }

    return boxFigure;
}

Generator::Generator()
{
    QTime midnight(0, 0, 0);
    qsrand(midnight.secsTo(QTime::currentTime()));
}

void Generator::initialize(Bootstrapper *boostrap)
{
    boardManager = boostrap->getBoardManager();
}
