#include "mainwindow.h"
#include "issuebook.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    mainWidget = new QWidget;
    mainWidget->setWindowTitle("Aurora's Integrated Library System");


    books = new Books(this);
    mainLayout = new QVBoxLayout();
    tabWidget = new QTabWidget;




    bIcon.addFile("book.png");
    sIcon.addFile("student.png");
    aIcon.addFile("admin.png");
    siz.setWidth(20);
    siz.setHeight(20);



    tabWidget->setTabPosition(QTabWidget::West);
    //tabWidget->setTabShape(QTabWidget::);
    tabWidget->addTab(books,bIcon,"books  ");
    tabWidget->addTab(new QWidget,sIcon,"Students  ");
    tabWidget->addTab(new QWidget,aIcon,"Admin  ");
    tabWidget->setIconSize(siz);



    mainLayout->addWidget(tabWidget);
    mainWidget->setLayout(mainLayout);
    mainWidget->show();
    //this->setMinimumSize(600,400);
    mainWidget->setMinimumSize(700,500);



}
