#ifndef GAMELOGICMANAGER_H
#define GAMELOGICMANAGER_H


#include <cell.h>
#include <Figures.h>
#include <QObject>
#include <BoardManager.h>
#include <QTimer>
class Bootstrapper;
class Generator;

class GameLogicManager : public QObject
{
    Q_OBJECT
public:
    explicit GameLogicManager(QObject *parent = nullptr);
    void initialize(Bootstrapper* boostrap);
    void nextStep();
    bool canPutFigureInBox(FigureBox &figureBox, QVector<CellInformation> &cellInformation);
    void putFigureInBoard(FigureBox &currentFigure, QVector<CellInformation> &cellInformation);

signals:
public slots:
    void downMoveFigure();

private:
    BoardManager * boardManager;
    Generator * m_generator;

    QTimer * timerDownMove;

    QVector<CellInformation> boardAllInformationСurrent;

    FigureBox nextFigure;
    FigureBox currentFigure;

    size_t indexHorizontalCenter;
};

#endif // GAMELOGICMANAGER_H
