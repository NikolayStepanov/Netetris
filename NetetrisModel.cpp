#include "NetetrisModel.h"

NetetrisModel::NetetrisModel()
{
    mediator=Mediator::getInstance();
}

void NetetrisModel::rotate()
{
    mediator->actionFigure(FigureAction::ROTATE);
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
