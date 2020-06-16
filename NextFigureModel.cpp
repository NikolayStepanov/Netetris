#include "NextFigureModel.h"
#include "mediator.h"

NextFigureModel::NextFigureModel(QObject *parent)
{
    mediator = Mediator::getInstance();
    mediator->initialize();
    connect(mediator,&Mediator::updateNextFigure,this,&NextFigureModel::slotUpdateNextFigure);
}

int NextFigureModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return 4;
}

int NextFigureModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return 4;
}

QVariant NextFigureModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    CellInformation cellInformation = mediator->getCellInformationNextFigure(index);

    switch (role)
    {
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

bool NextFigureModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) == value)
        return false;

    emit dataChanged(index, index, {role});

    return true;
}

Qt::ItemFlags NextFigureModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

void NextFigureModel::slotUpdateNextFigure()
{
     emit dataChanged(index(0,0),index(3,3));
}
