#ifndef GENERATOR_H
#define GENERATOR_H

#include <QVector>

struct CellInformation;
struct Figure;

class Generator
{
public:
    static Generator *getInstance();
    ~Generator();
    QString randomColor();
    Figure randomFigure();
    QVector<CellInformation> emptyBox4x4ForFigure();
private:
    Generator();
    Generator( const Generator& );
    Generator& operator=( Generator& );
private:
    static Generator * p_instance;
};

#endif // GENERATOR_H
