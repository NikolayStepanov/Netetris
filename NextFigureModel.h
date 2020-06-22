#ifndef NEXTFIGUREMODEL_H
#define NEXTFIGUREMODEL_H

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
    explicit NextFigureModel(QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

public slots:
    void slotUpdateNextFigure();

private:
    Mediator * mediator;
};

#endif // NEXTFIGUREMODEL_H
