#ifndef ACTIONS_H
#define ACTIONS_H

#include <QWidget>
#include <QAction>
#include <QTableView>

class Actions : public QWidget
{
    Q_OBJECT
public:
    explicit Actions();
    QAction *addBookAction;

    
signals:
    
public slots:
    
};

#endif // ACTIONS_H
/*
openAct = new QAction(QIcon(":/images/open.png"), tr("&Open..."), this);
     openAct->setShortcuts(QKeySequence::Open);
     openAct->setStatusTip(tr("Open an existing file"));
     connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

     fileMenu->addAction(openAct);
*/
