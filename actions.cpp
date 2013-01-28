#include "actions.h"

Actions::Actions()
{
    addBookAction = new QAction("add book", this);
    QObject::connect(this->addBookAction,SIGNAL(triggered()),this,SLOT(update()));
}
