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
    BoardManager();
    ~BoardManager();

    void initialize(Bootstrapper* boostrap);

    bool createBoard(size_t width,size_t height);

    size_t getWidthBoard() const;
    size_t getHeightBoard() const;
    size_t getNumderCells() const;
    QPair <size_t,size_t> getSizeBoard() const;

    void setCellInformation(const CellInformation cellInformation);
    void clearRow(size_t row);
    void clearColumn(size_t column);
    void clearCell(size_t cellIndex);

    CellInformation getCellInformation(size_t cellIndex) const;
    QVector<CellInformation> getAllCellsInformation() const;
    QList<CellInformation>getCellsInformation(QList<size_t> cellIndices) const;
    QList<CellInformation>getCellsInformation(QList<QPoint> cellPoints) const;

    bool areCellIndexValid(size_t cellIndex) const;
    bool areCellCoordinatesValid(const QPoint &coordinates) const;

    QVector<QPoint> cellsCoordinatesFromIndices(QVector<size_t> cellIndices) const;
    QPoint cellCoordinatesFromIndex(size_t cellIndex) const;

    size_t cellIndex(const QPoint &coordinates) const;
    size_t cellIndex(const QModelIndex &index) const;

signals:
    void updateCell(size_t index);
    void updateRow(size_t row);
    void updateColumn(size_t column);

private:
    Board * board;
};

#endif // BOARDMANAGER_H
