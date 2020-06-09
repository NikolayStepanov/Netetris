#include "boardmodel.h"
#include "mediator.h"

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
        return QVariant(cellInformation.x);
        break;
    case YCell:
        return QVariant(cellInformation.y);
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

BoardModel::BoardModel(QObject *parent)
{
    mediator = Mediator::getInstance();
    mediator->initialize();
}
