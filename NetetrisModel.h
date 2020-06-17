#ifndef NETETRISMODEL_H
#define NETETRISMODEL_H

#include <QObject>
#include "common.h"

class Mediator;
class NetetrisModel:public QObject
{
    Q_OBJECT
public:
    explicit NetetrisModel(QObject *parent = nullptr);

    Q_INVOKABLE void newGame();
    Q_INVOKABLE void startGame();
    Q_INVOKABLE void stopGame();
    Q_INVOKABLE void quitGame();

    Q_INVOKABLE void rotate();
    Q_INVOKABLE void moveDown();
    Q_INVOKABLE void moveLeft();
    Q_INVOKABLE void moveRight();

private:
    Mediator * mediator;
};

#endif // NETETRISMODEL_H
