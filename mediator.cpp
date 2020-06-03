#include "mediator.h"

Mediator * Mediator::p_instance = nullptr;

Mediator::Mediator(QObject *parent):
    QObject(parent)
{

}

Mediator *Mediator::getInstance()
{
    if(!p_instance)
        p_instance = new Mediator();
    return p_instance;
}
