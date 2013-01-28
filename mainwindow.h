#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include "books.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QWidget *mainWidget;
    QTabWidget *tabWidget;
    QVBoxLayout* mainLayout;
    Books *books;
public:
    explicit MainWindow(QWidget *parent = 0);

    
signals:
    
public slots:
    
};

#endif // MAINWINDOW_H
