#include "NetetrisModel.h"
#include "mediator.h"

NetetrisModel::NetetrisModel(QObject *parent):
    QObject(parent)
{
    mediator = Mediator::getInstance();
    m_numberLines = 0;

    connect(mediator, &Mediator::updateNumberLines, this, &NetetrisModel::slotLinesChanged);
    connect(mediator, &Mediator::gameOver, this, &NetetrisModel::gameOver);
}

void NetetrisModel::setLines(int &lines)
{
    if(lines != m_numberLines)
    {
        m_numberLines = lines;
        emit linesChanged(m_numberLines);
    }
}

void NetetrisModel::newGame()
{
    mediator->newGame();
}

void NetetrisModel::startGame()
{

}

void NetetrisModel::stopGame()
{

}

void NetetrisModel::quitGame()
{

}

void NetetrisModel::fixFigure()
{
    mediator->actionFigure(FigureAction::FIX);
}

void NetetrisModel::rotate()
{
    mediator->actionFigure(FigureAction::ROTATE);
}

void NetetrisModel::moveTop()
{
    mediator->actionFigure(FigureAction::MOVE_TOP);
}

void NetetrisModel::moveDown()
{
    mediator->actionFigure(FigureAction::MOVE_DOWN);
}

void NetetrisModel::moveLeft()
{
    mediator->actionFigure(FigureAction::MOVE_LEFT);
}

void NetetrisModel::moveRight()
{
    mediator->actionFigure(FigureAction::MOVE_RIGHT);
}

int NetetrisModel::number_lines()
{
    return m_numberLines;
}

void NetetrisModel::slotLinesChanged(int lines)
{
    m_numberLines = lines;
    emit linesChanged(m_numberLines);
}
