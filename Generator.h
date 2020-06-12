#ifndef Generator_H
#define Generator_H

#include <QVector>
#include <common.h>
class Bootstrapper;
struct CellInformation;
struct FigureBox;

class Generator
{
public:
    Generator();
    void initialize(Bootstrapper* boostrap);
    ~Generator();
    QString randomColor();
    FigureBox randomFigure();
    QVector<CellInformation> emptyBox4x4ForFigure();
};

#endif // Generator_H
