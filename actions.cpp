#include "actions.h"

Actions::Actions()
{
    //qDebug() << "Actions constructed";
    addBookAction = new QAction("add book", this);
    QObject::connect(this->addBookAction,SIGNAL(triggered()),this,SLOT(update()));

}
