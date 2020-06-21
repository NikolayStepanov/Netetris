#ifndef Generator_H
#define Generator_H

#include <QVector>

#include "common.h"

class Bootstrapper;
class BoardManager;

struct CellInformation;
struct FigureBox;

class Generator
{
public:
    Generator();

    void initialize(Bootstrapper* boostrap);

    QString randomColor();
    FigureBox randomFigure();
    QVector<CellInformation> emptyBox4x4ForFigure();

private:
    BoardManager * boardManager;
};

#endif // Generator_H
