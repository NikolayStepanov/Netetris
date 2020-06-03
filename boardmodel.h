#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#include <QAbstractTableModel>

class BoardModel: public QAbstractTableModel
{
    Q_OBJECT
    Q_ENUMS(CellRoles)
public:
    enum CellRoles
    {
        XCell,
        YCell,
        IndexCell,
        TypeCell,
        ColorCell

    };
    BoardModel();
};

#endif // BOARDMODEL_H
