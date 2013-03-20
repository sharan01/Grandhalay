#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include "books.h"
#include "admin.h"

class MainWindow : public QWidget
{
    Q_OBJECT
private:
    QWidget *mainWidget;
    QTabWidget *tabWidget;
    QVBoxLayout* mainLayout;
    Books *books;
    Admin *admin;
    QIcon bIcon;
    QIcon sIcon;
    QIcon aIcon;
    QSize siz;

public:
    explicit MainWindow(QWidget *parent = 0);
    void createResources();
    void createWidgets();
    void createLayout();
    void createConnections();


    
signals:
    
public slots:
    
};

#endif // MAINWINDOW_H
