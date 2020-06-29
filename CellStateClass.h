#ifndef CELLSTATECLASS_H
#define CELLSTATECLASS_H

#include <QObject>

class CellStateClass
{
    Q_GADGET
public:
    explicit CellStateClass();

    enum Value {
        EMPTY,
        NOT_FIXED,
        FIXED
    };
    Q_ENUM(Value)
};

#endif // CELLSTATECLASS_H
