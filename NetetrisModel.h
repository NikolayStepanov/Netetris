#ifndef NETETRISMODEL_H
#define NETETRISMODEL_H

#include <QObject>

#include "common.h"

class Mediator;

class NetetrisModel:public QObject
{
    Q_OBJECT
    Q_PROPERTY(int number_lines READ number_lines WRITE setLines NOTIFY linesChanged)

public:
    explicit NetetrisModel(QObject *parent = nullptr);

    void setLines(int &lines);

    Q_INVOKABLE void newGame();
    Q_INVOKABLE void startGame();
    Q_INVOKABLE void stopGame();
    Q_INVOKABLE void quitGame();

    Q_INVOKABLE void fixFigure();
    Q_INVOKABLE void rotate();
    Q_INVOKABLE void moveTop();
    Q_INVOKABLE void moveDown();
    Q_INVOKABLE void moveLeft();
    Q_INVOKABLE void moveRight();

    Q_INVOKABLE int number_lines();

signals:
    void linesChanged(int lines);
    void gameOver();

public slots:
    void slotLinesChanged(int lines);

private:
    Mediator * mediator;
    int m_numberLines;
};

#endif // NETETRISMODEL_H
