#ifndef BOARDMANAGER_H
#define BOARDMANAGER_H

#include <QObject>

#include "common.h"


class Bootstrapper;
class Board;

class BoardManager:public QObject
{
    Q_OBJECT
public:
    void initialize(Bootstrapper* boostrap);
    BoardManager();
    ~BoardManager();

    bool createBoard(size_t width,size_t height);

    size_t getWidthBoard() const;
    size_t getHeightBoard() const;
    QPair <size_t,size_t> getSizeBoard() const;

    void setCellInformation(const CellInformation cellInformation);

    CellInformation getCellInformation(const size_t cellIndex) const;
    QVector<CellInformation> getAllCellsInformation() const;
    QList<CellInformation>getAllCellsInformation(const QList<size_t> cellIndices) const;

    bool areCellIndexValid(const size_t cellIndex) const;
    bool areCellCoordinatesValid(const QPoint &coordinates) const;

    QPoint cellCoordinatesFromIndex(const size_t cellIndex) const;

    size_t cellIndex(const QPoint &coordinates) const;
    size_t cellIndex(const QModelIndex &index) const;

signals:

private:
    Board * board;
};

#endif // BOARDMANAGER_H
