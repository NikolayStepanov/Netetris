#ifndef NEXTFIGUREMODEL_H
#define NEXTFIGUREMODEL_H

#include <QObject>
#include <QAbstractTableModel>

class Mediator;

class NextFigureModel:public QAbstractTableModel
{
    Q_OBJECT
    Q_ENUMS(NextFigureRoles)
public:
    enum NextFigureRoles
    {
        IndexCell,
        TypeCell,
        ColorCell
    };

    QHash<int, QByteArray> roleNames() const override
    {
        QHash<int, QByteArray> roles;
        roles[IndexCell] = "indexCell";
        roles[TypeCell] = "typeCell";
        roles[ColorCell] = "colorCell";
        return roles;
    }

    explicit NextFigureModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value,int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

public slots:
    void slotUpdateNextFigure();

private:
    Mediator * mediator;
};

#endif // NEXTFIGUREMODEL_H
