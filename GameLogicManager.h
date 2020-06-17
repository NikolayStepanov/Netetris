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

    void newGame();
    void gameOver();

    void startGame();
    void stopGame();

    void nextStep();
    void generateNextFigure();

    CellInformation getCellNextFigure(QPoint coordinat);

    bool deleteWholeLines();
    bool deleteColumns();
    bool deleteRows();

    bool canPutFigureInBox(FigureBox &figureBox, QVector<CellInformation> &cellInformationBox);
    void deleteFigureinInBoard(FigureBox &currentFigure);
    void putFigureInBoard(FigureBox &currentFigure, QVector<CellInformation> &cellInformationBox);

    QVector<CellInformation> getCellsInformationBoxCurrentFigure(QPoint coordinateOffset);

    bool moveFigure(QPoint coordinateOffset);
    bool rotationFigure();
    FigureBox rotationFigureInBox(FigureBox figureBox);

    bool cellsContainedInBox(QVector<CellInformation> cellsInformation, FigureBox figureBox) const;

signals:
    void updateNextFigure();

public slots:
    void actionFigure(FigureAction actionFigure = FigureAction::MOVE_DOWN);

private:
    BoardManager * boardManager;
    Generator * m_generator;

    QTimer * timerDownMove;

    QVector<CellInformation> boardAllInformationCurrent;

    FigureBox nextFigure;
    FigureBox currentFigure;

    size_t indexHorizontalCenter;
    int horizontalLineMaxFigures;
};

#endif // GAMELOGICMANAGER_H
