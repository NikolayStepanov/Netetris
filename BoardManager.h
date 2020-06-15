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
    size_t getNumderCells() const;
    QPair <size_t,size_t> getSizeBoard() const;

    void setCellInformation(const CellInformation cellInformation);
    void clearRow(size_t row);
    void clearCell(const size_t cellIndex);

    CellInformation getCellInformation(const size_t cellIndex) const;
    QVector<CellInformation> getAllCellsInformation() const;
    QList<CellInformation>getCellsInformation(const QList<size_t> cellIndices) const;
    QList<CellInformation>getCellsInformation(const QList<QPoint> cellPoints) const;

    bool areCellIndexValid(const size_t cellIndex) const;
    bool areCellCoordinatesValid(const QPoint &coordinates) const;

    QVector<QPoint> cellsCoordinatesFromIndices(QVector<size_t> cellIndices) const;
    QPoint cellCoordinatesFromIndex(size_t cellIndex) const;

    size_t cellIndex(const QPoint &coordinates) const;
    size_t cellIndex(const QModelIndex &index) const;

signals:
    void updateCell(size_t index);
    void updateRow(size_t row);

private:
    Board * board;
};

#endif // BOARDMANAGER_H
