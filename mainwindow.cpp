#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    mainWidget = new QWidget;
    mainWidget->setWindowTitle("Aurora's Integrated Library System");


    books = new Books();
    mainLayout = new QVBoxLayout();
    tabWidget = new QTabWidget;
    tabWidget->setTabPosition(QTabWidget::West);
    //tabWidget->setTabShape(QTabWidget::Triangular);
    tabWidget->addTab(books,"books");



    mainLayout->addWidget(tabWidget);
    mainWidget->setLayout(mainLayout);
    mainWidget->show();
}
