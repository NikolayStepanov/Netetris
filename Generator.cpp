#include "Generator.h"

#include <QTime>
#include <Figures.h>
#include "common.h"

Generator * Generator::p_instance = nullptr;

Generator *Generator::getInstance()
{
    if(!p_instance)
        p_instance = new Generator();
    return p_instance;
}

Generator::~Generator()
{

}

QString Generator::randomColor()
{
    Color color = static_cast<Color>(qrand()%(number_color-2)+2);
    return strColor(color);
}

Figure Generator::randomFigure()
{
    QVector<CellInformation> figureCells = emptyBox4x4ForFigure();
    QString color = randomColor();
    Figure figureRand;

    FigureType typeFigure = static_cast<FigureType>(qrand()% number_figures);

    for(auto index:figures[typeFigure])
    {
        figureCells[index].type = typeFigure;
        figureCells[index].color = color;
    }
    figureRand.cellsInformation = figureCells;
    figureRand.color = QColor(color);

    return figureRand;
}

QVector<CellInformation> Generator::emptyBox4x4ForFigure()
{
    QVector<CellInformation> boxFigure;
    for(int i = 0; i< number_cells_for_figure; i++)
    {
        boxFigure.push_back(CellInformation(static_cast<size_t>(i)));
    }
    return boxFigure;
}

Generator::Generator()
{
    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));
}
