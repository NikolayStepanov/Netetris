#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#include <QAbstractTableModel>
#include <QObject>

class Mediator;

class BoardModel: public QAbstractTableModel
{
    Q_OBJECT
    Q_ENUMS(CellRoles)
    Q_PROPERTY(int row READ getRow)
    Q_PROPERTY(int colum READ getColum)

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
        roles[XCell] = "xCell";
        roles[YCell] = "yCell";
        roles[IndexCell] = "indexCell";
        roles[TypeCell] = "typeCell";
        roles[ColorCell] = "colorCell";
        return roles;
    }

    explicit BoardModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value,int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    Q_INVOKABLE int getRow() const;
    Q_INVOKABLE int getColum() const;

public slots:
    void slotCellUpdate(size_t indexCell);
    void slotRowUpdate(size_t row);

private:
    Mediator * mediator;

};

#endif // BOARDMODEL_H
