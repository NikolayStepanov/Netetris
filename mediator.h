#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <QObject>

#include "common.h"

class BoardManager;
class GameLogicManager;
class Bootstrapper;

class Mediator: public QObject
{
    Q_OBJECT
public:
    static Mediator *getInstance();

    void initialize();
    ~Mediator();

    //BoardManager
    int getRowCountBoard() const;
    int getColumnCountBoard() const;

    size_t getWidthBoard() const;
    size_t getHeightBoard() const;
    CellInformation getCellInformation(const QModelIndex &index);
    QPoint getPointForIndex(size_t index);

    //GameLogicManager
    CellInformation getCellInformationNextFigure(const QModelIndex &index);

    void actionFigure(FigureAction actionFigure);
    void newGame();

    bool isBorder(QPoint coordinate)const;
    int getNumberLines();

    QPoint minCoordinateBorder() const;
    QPoint maxCoordinateBorder() const;

signals:
    void updateCell(size_t index);
    void updateRow(size_t row);
    void updateColumn(size_t column);
    void updateNextFigure();
    void updateNumberLines(int lines);

public slots:
    void slotUpdateCell(size_t index);
    void slotUpdateRow(size_t row);
    void slotUpdateColumn(size_t column);
    void slotUbdateNextFigure();
    void slotUpdateNumberLines(int lines);

private:
    Mediator(QObject *parent = nullptr);
    Mediator( const Mediator& );
    Mediator& operator=( Mediator& );

private:
    static Mediator * p_instance;

    BoardManager * boardManager;
    Bootstrapper * bootstrapper;
    GameLogicManager * gameLogicManager;

};

#endif // MEDIATOR_H
