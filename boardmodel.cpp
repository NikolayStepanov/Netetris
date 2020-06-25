#include "boardmodel.h"

#include <QPoint>

#include "common.h"
#include "mediator.h"

BoardModel::BoardModel(QObject *parent):
    QAbstractTableModel(parent)
{
    mediator = Mediator::getInstance();
    mediator->initialize();

    connect(mediator, &Mediator::updateCell, this, &BoardModel::slotCellUpdate);
    connect(mediator, &Mediator::updateRow, this, &BoardModel::slotRowUpdate);
    connect(mediator, &Mediator::updateColumn, this, &BoardModel::slotColumnUpdate);
}

QHash<int, QByteArray> BoardModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[XCell] = "xCell";
    roles[YCell] = "yCell";
    roles[IndexCell] = "indexCell";
    roles[TypeCell] = "typeCell";
    roles[ColorCell] = "colorCell";
    return roles;
}

int BoardModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return mediator->getRowCountBoard();
}

int BoardModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return mediator->getColumnCountBoard();
}

QVariant BoardModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    CellInformation cellInformation = mediator->getCellInformation(index);

    switch (role)
    {
    case XCell:
        return QVariant(cellInformation.coordinate.x());
    case YCell:
        return QVariant(cellInformation.coordinate.y());
    case IndexCell:
        return QVariant(cellInformation.index);
    case TypeCell:
        return QVariant(cellInformation.type);
    case ColorCell:
        return QVariant(cellInformation.color);
    default:
        return QVariant();
    }
}

int BoardModel::getRow() const
{
    return mediator->getRowCountBoard();
}

int BoardModel::getColum() const
{
    return mediator->getColumnCountBoard();
}

bool BoardModel::isBorder(int x, int y) const
{
    return mediator->isBorder(QPoint(x, y));
}

void BoardModel::slotCellUpdate(size_t indexCell)
{
    QPoint pointUpdate = mediator->getPointForIndex(indexCell);
    QModelIndex indexUpdate = index(pointUpdate.y(), pointUpdate.x());
    emit dataChanged(indexUpdate, indexUpdate);
}

void BoardModel::slotRowUpdate(size_t row)
{
    emit dataChanged(index(row, 0), index(row,mediator->getWidthBoard() - 1));
}

void BoardModel::slotColumnUpdate(size_t colunm)
{
    emit dataChanged(index(0, colunm), index(mediator->getHeightBoard() - 1, colunm));
}

