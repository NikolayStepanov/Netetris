#include "Generator.h"
#include <bootstrapper.h>
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
    QString color = randomColor();
    FigureType typeFigure = static_cast<FigureType>(qrand()% number_figures);

    FigureBox figureRandBox;
    figureRandBox.cellsInformation = emptyBox4x4ForFigure();
    figureRandBox.color = QColor(color);
    figureRandBox.type = typeFigure;
    figureRandBox.indicesNonEmptyCell = figures[typeFigure];

    for(auto index:figureRandBox.indicesNonEmptyCell)
    {
        figureRandBox.cellsInformation[index].type = typeFigure;
        figureRandBox.cellsInformation[index].color = color;
    }

    return figureRandBox;
}

QVector<CellInformation> Generator::emptyBox4x4ForFigure()
{
    QVector<CellInformation> boxFigure;
    boxFigure.reserve(number_cells_for_figure);

    for(int i = 0; i< number_cells_for_figure; i++)
    {
        boxFigure.push_back(CellInformation());
    }

    int index = 0;
    int xStart = (boardManager->getWidthBoard()/2)-2;
    for(int y=-4;y<0;y++)
    {
        for(int x=xStart;x<(xStart+4);x++)
        {
            boxFigure[index].coordinates.setX(x);
            boxFigure[index].coordinates.setY(y);
            index++;
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
    boardManager = boostrap->getBoardManager();
}
