#ifndef CELLACTIONCLASS_H
#define CELLACTIONCLASS_H

#include <QObject>

class CellActionClass
{
    Q_GADGET
public:
    explicit CellActionClass();

    enum Value {
        EMPTY,
        OVERLAP,
        PROMPT
    };
    Q_ENUM(Value)
};
#endif // CELLACTIONCLASS_H
