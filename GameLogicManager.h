#ifndef GAMELOGICMANAGER_H
#define GAMELOGICMANAGER_H

#include <QTimer>
#include <QObject>

#include "cell.h"
#include "Figures.h"

class Bootstrapper;
class Generator;
class BoardManager;
class AnalystManager;

class GameLogicManager : public QObject
{
    Q_OBJECT
public:
    explicit GameLogicManager(QObject *parent = nullptr);
    ~GameLogicManager();
    void initialize(Bootstrapper* boostrap);

    void hintWherePlaceFigure(FigureBox figure);
    void removeHint();

    void newGame();
    void finishGame();
    bool endGame();

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
    void deleteFigureInBoard(FigureBox &currentFigure);
    void putFigureInBoard(FigureBox &currentFigure, QVector<CellInformation> &cellInformationBox);

    QVector<CellInformation> getCellsInformationBoxFigure(FigureBox figureBox, QPoint coordinateOffset);

    bool moveFigure(QPoint coordinateOffset = QPoint(0, 0));

    bool fixCurrentFigure();
    bool canFixFigureOnBoard(FigureBox &figure) const;

    bool rotationFigure();
    FigureBox rotationFigureInBox(FigureBox figureBox);

    bool cellsContainedInBox(QVector<CellInformation> cellsInformation, FigureBox figureBox) const;

    //get
    bool getNumberLines() const;
    bool isCoordinateBorder(QPoint coordinate) const;

    QPoint getMinXY() const;
    QPoint getMaxXY() const;

    QVector<CellInformation>getRowBoardCurrentCellInformation(int rowNumber);
    QVector<CellInformation>getColumnBoardCurrentCellInformation(int columnNumber);

    CellInformation getCellBoardCurrentCellInformation(QPoint coordinateCell);


    QVector<CellInformation> getBoardAllInformationCurrent();

    //set
    void setNumberLines(int numberLines);
    void initialCoordinatesFigure(FigureBox &figure);

signals:
    void updateNextFigure();
    void updateNumberLines(int lines);
    void gameOver();

public slots:
    void actionFigure(FigureAction actionFigure = FigureAction::MOVE_DOWN);
    void activateHint();

private:
    BoardManager * m_pBoardManager;
    Generator * m_pGenerator;
    AnalystManager * m_pAnalystManager;

    QVector<CellInformation> m_boardAllInformationCurrent;

    FigureBox m_bestPositionCurrentFigure;

    FigureBox m_nextFigure;
    FigureBox m_currentFigure;

    int m_numberLines;

    QPoint m_minXY;
    QPoint m_maxXY;

    QTimer * m_pHintDisplayTimer;
};

#endif // GAMELOGICMANAGER_H
