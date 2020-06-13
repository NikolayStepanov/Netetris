#ifndef NETETRISMODEL_H
#define NETETRISMODEL_H

#include <QObject>
#include <mediator.h>
#include "common.h"

class NetetrisModel:public QObject
{
    Q_OBJECT
public:
    NetetrisModel();
    Q_INVOKABLE void rotate();
    Q_INVOKABLE void moveDown();
    Q_INVOKABLE void moveLeft();
    Q_INVOKABLE void moveRight();

private:
    Mediator * mediator;
};

#endif // NETETRISMODEL_H
