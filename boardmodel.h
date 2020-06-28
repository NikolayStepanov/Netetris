#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#include <QAbstractTableModel>

#include "common.h"

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
        StateCell,
        ActionCell,
        FigureType,
        ColorCell,
    };

    explicit BoardModel(QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE int getRow() const;
    Q_INVOKABLE int getColum() const;
    Q_INVOKABLE bool isBorder(int x,int y) const;

public slots:
    void slotCellUpdate(size_t indexCell);
    void slotRowUpdate(size_t row);
    void slotColumnUpdate(size_t colunm);

private:
    Mediator * mediator;
};

#endif // BOARDMODEL_H
