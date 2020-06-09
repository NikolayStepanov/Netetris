#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#include <QAbstractTableModel>
#include <QObject>

class Mediator;

class BoardModel: public QAbstractTableModel
{
    Q_OBJECT
    Q_ENUMS(CellRoles)
    Q_PROPERTY(int getRow READ getRow)
    Q_PROPERTY(int getColum READ getColum)

public:
    enum CellRoles
    {
        XCell,
        YCell,
        IndexCell,
        TypeCell,
        ColorCell

    };

    QHash<int, QByteArray> roleNames() const override
    {
        QHash<int, QByteArray> roles;
        roles[XCell] = "x";
        roles[YCell] = "y";
        roles[IndexCell] = "index";
        roles[TypeCell] = "type";
        roles[ColorCell] = "color";
        return roles;
    }

    explicit BoardModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    Q_INVOKABLE int getRow() const;
    Q_INVOKABLE int getColum() const;
private:
    Mediator * mediator;

};

#endif // BOARDMODEL_H
