#ifndef GAMELOGICMANAGER_H
#define GAMELOGICMANAGER_H

#include <QObject>
#include <cell.h>
#include <Figures.h>

class Bootstrapper;
class BoardManager;

class GameLogicManager : public QObject
{
    Q_OBJECT
public:
    explicit GameLogicManager(QObject *parent = nullptr);

    void initialize(Bootstrapper* boostrap);

signals:

private:
    BoardManager * boardManager;
    Figure nextFigure;
    Figure currentFigure;
};

#endif // GAMELOGICMANAGER_H
