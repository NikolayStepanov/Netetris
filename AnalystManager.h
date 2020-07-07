#ifndef ANALYSTMANAGER_H
#define ANALYSTMANAGER_H

#include <QObject>

#include "common.h"
#include "Figures.h"

class Bootstrapper;
class GameLogicManager;

class AnalystManager : public QObject
{
     Q_OBJECT
public:

    AnalystManager();

    void initialize(Bootstrapper* boostrap);

    int howManyLinesDeletion(FigureBox figurePosition) const;

    int howManyNeighborsFigure(FigureBox figurePosition) const;

    int weightPositionFigure(FigureBox figurePosition) const;

private:
    GameLogicManager *m_pGameLogicManager;

};

#endif // ANALYSTMANAGER_H
