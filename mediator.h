#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <QObject>

class Mediator: public QObject
{
    Q_OBJECT
public:
    static Mediator *getInstance();
    ~Mediator();

private:
    Mediator(QObject *parent = nullptr);
    Mediator( const Mediator& );
    Mediator& operator=( Mediator& );

private:
    static Mediator * p_instance;

};

#endif // MEDIATOR_H
