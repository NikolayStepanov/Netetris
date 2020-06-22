#include "NextFigureModel.h"

#include "mediator.h"

NextFigureModel::NextFigureModel(QObject *parent):
    QAbstractTableModel(parent)
{
    mediator = Mediator::getInstance();
    mediator->initialize();

    connect(mediator,&Mediator::updateNextFigure,this,&NextFigureModel::slotUpdateNextFigure);
}

QHash<int, QByteArray> NextFigureModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IndexCell] = "indexCell";
    roles[TypeCell] = "typeCell";
    roles[ColorCell] = "colorCell";
    return roles;
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

void NextFigureModel::slotUpdateNextFigure()
{
    emit dataChanged(index(0,0),index(3,3));
}
