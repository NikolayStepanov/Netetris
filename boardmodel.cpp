#include "boardmodel.h"
#include "mediator.h"
#include <QPoint>
#include "common.h"

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
        return QVariant(cellInformation.coordinates.x());
        break;
    case YCell:
        return QVariant(cellInformation.coordinates.y());
        break;
    case IndexCell:
        return QVariant(cellInformation.index);
        break;
    case TypeCell:
        return QVariant(cellInformation.type);
        break;
    case ColorCell:
        return QVariant(cellInformation.color);
    default:
        return QVariant();
    }
}

bool BoardModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) == value)
        return false;

    emit dataChanged(index, index, {role});

    return true;
}

Qt::ItemFlags BoardModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

int BoardModel::getRow() const
{
    return mediator->getRowCountBoard();
}

int BoardModel::getColum() const
{
    return mediator->getColumnCountBoard();
}

void BoardModel::slotCellUpdate(size_t indexCell)
{
    QPoint pointUpdate = mediator->getPointForIndex(indexCell);
    QModelIndex indexUpdate = index(pointUpdate.y(),pointUpdate.x());
    emit dataChanged(indexUpdate,indexUpdate);
}

void BoardModel::slotRowUpdate(size_t row)
{
    emit dataChanged(index(row,0),index(row,mediator->getWidthBoard()-1));
}

void BoardModel::slotColumnUpdate(size_t colunm)
{
    emit dataChanged(index(0,colunm),index(mediator->getHeightBoard()-1,colunm));
}

BoardModel::BoardModel(QObject *parent)
{
    mediator = Mediator::getInstance();
    mediator->initialize();

    connect(mediator,&Mediator::updateCell,this,&BoardModel::slotCellUpdate);
    connect(mediator,&Mediator::updateRow,this,&BoardModel::slotRowUpdate);
    connect(mediator,&Mediator::updateColumn,this,&BoardModel::slotColumnUpdate);
}
