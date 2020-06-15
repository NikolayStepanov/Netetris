#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <QObject>

#include <common.h>

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

    //BoardModel
    int getRowCountBoard();
    int getColumnCountBoard();

    //BoardManager
    size_t getWidthBoard();
    size_t getHeightBoard();
    CellInformation getCellInformation(const QModelIndex &index);
    QPoint getPointForIndex(size_t index);

    //GameLogic
    void moveDown();
    void moveLeft();
    void moveRight();
    void actionFigure(FigureAction actionFigure);

signals:
    void updateCell(size_t index);
    void updateRow(size_t row);

public slots:
    void slotUpdateCell(size_t index);
    void slotUpdateRow(size_t row);

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
