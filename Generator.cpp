#include "Generator.h"

#include <QTime>
#include <Figures.h>

Generator::~Generator()
{

}

QString Generator::randomColor()
{
    Color color = static_cast<Color>(qrand()%(number_color-2)+2);
    return strColor(color);
}

FigureBox Generator::randomFigure()
{
    QVector<CellInformation> figureCells = emptyBox4x4ForFigure();
    QString color = randomColor();
    FigureBox figureRandBox;

    FigureType typeFigure = static_cast<FigureType>(qrand()% number_figures);

    for(auto index:figures[typeFigure])
    {
        figureCells[index].type = typeFigure;
        figureCells[index].color = color;
    }
    figureRandBox.cellsInformation = figureCells;
    figureRandBox.color = QColor(color);

    return figureRandBox;
}

QVector<CellInformation> Generator::emptyBox4x4ForFigure()
{
    QVector<CellInformation> boxFigure(number_cells_for_figure);

    for(int i = 0; i< number_cells_for_figure; i++)
    {
        boxFigure.push_back(CellInformation());
    }

    int index = 0;

    for(size_t y=SIZE_MAX-3;y<=SIZE_MAX;y++)
    {
        for(size_t x=SIZE_MAX-3;x<=SIZE_MAX;x++)
        {
            boxFigure[index].x=x;
            boxFigure[index].y=y;
        }
    }

    return boxFigure;
}

Generator::Generator()
{
    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));
}

void Generator::initialize(Bootstrapper *boostrap)
{

}
