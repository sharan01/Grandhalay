#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "books.h"
#include "members.h"
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
    Members *members;
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
