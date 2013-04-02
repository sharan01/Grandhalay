#include "mainwindow.h"
#include "issuebook.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    qDebug() << "main window constructed";

    createResources();
    createWidgets();
    createLayout();
}
void MainWindow::createResources()
{
    bIcon.addFile(":/images/book.png");
    sIcon.addFile(":/images/student.png");
    aIcon.addFile(":/images/admin.png");
    siz.setWidth(20);
    siz.setHeight(20);
}

void MainWindow::createWidgets()
{
    mainWidget = new QWidget(this);
    tabWidget = new QTabWidget(this);
    books = new Books(this);
    members = new Members(this);
    admin = new Admin(this);

    mainWidget->setWindowTitle("Aurora's Integrated Library System");


    tabWidget->addTab(books,bIcon,"books  ");
    tabWidget->addTab(members,sIcon,"Students  ");
    tabWidget->addTab(admin,aIcon,"Admin  ");

    tabWidget->setTabPosition(QTabWidget::West);
    tabWidget->setIconSize(siz);

}
void MainWindow::createLayout()
{
    mainLayout = new QVBoxLayout();

    mainLayout->addWidget(tabWidget);
    mainWidget->setLayout(mainLayout);
    mainWidget->show();
    mainWidget->setMinimumSize(700,500);

}
void MainWindow::createConnections()
{

}
