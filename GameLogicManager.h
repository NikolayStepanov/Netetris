#ifndef GAMELOGICMANAGER_H
#define GAMELOGICMANAGER_H

#include <QTimer>
#include <QObject>

#include "cell.h"
#include "Figures.h"

class Bootstrapper;
class Generator;
class BoardManager;

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

    void addLinesPoints();

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

    bool moveFigure(QPoint coordinateOffset = QPoint(0,0));
    bool fixCurrentFigure();
    bool rotationFigure();
    FigureBox rotationFigureInBox(FigureBox figureBox);

    bool cellsContainedInBox(QVector<CellInformation> cellsInformation, FigureBox figureBox) const;

    //get
    bool getNumberLines() const;
    bool isCoordinateBorder(QPoint coordinate) const;
    QPoint getMinXY() const;
    QPoint getMaxXY() const;

signals:
    void updateNextFigure();
    void updateNumberLines(int lines);

public slots:
    void actionFigure(FigureAction actionFigure = FigureAction::MOVE_DOWN);

private:
    BoardManager * m_pBoardManager;
    Generator * m_pGenerator;

    QVector<CellInformation> m_boardAllInformationCurrent;

    FigureBox m_nextFigure;
    FigureBox m_currentFigure;

    int m_numberLines;

    QPoint m_minXY;
    QPoint m_maxXY;
};

#endif // GAMELOGICMANAGER_H
