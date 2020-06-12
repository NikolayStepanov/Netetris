#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <QObject>

#include <common.h>

class BoardManager;
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

signals:
    void updateCell(size_t index);

public slots:
    void slotUpdateCell(size_t index);

private:
    Mediator(QObject *parent = nullptr);
    Mediator( const Mediator& );
    Mediator& operator=( Mediator& );

private:
    static Mediator * p_instance;

    BoardManager * boardManager;
    Bootstrapper * bootstrapper;

};

#endif // MEDIATOR_H
