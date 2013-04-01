#include "welcome.h"
#include "mainwindow.h"
#include <QtCore>
#include <QtSql/QtSql>
#include <memory>

//#define PATH_TO_DB "/home/srn/Documents/ils/ils/ils.sqlite"
#define PATH_TO_DB "/home/srn/Documents/ils/ils.sqlite"


using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Aurora's Integrates Library System");
    QIcon ico;
    ico.addFile("icon.png");
    app.setWindowIcon(ico);

    // db connection
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE"); //  delete in destructor
    db.setDatabaseName(PATH_TO_DB);
    qDebug() << db.databaseName();
    if(db.open()){
        qDebug() << "db open";
    }else{
        qDebug() << "db not open !!!";
    }


    QSqlQuery q("select * from books;");
    if(q.exec()){
        qDebug() << "quer done";
    }else{
        qDebug() << "query fail";
    }

    unique_ptr<Welcome> w(new Welcome);
    unique_ptr<MainWindow> mw(new MainWindow);
    //MainWindow *mw = new MainWindow;

    /*
    w->show();

    QObject::connect(w->loginButton,SIGNAL(clicked()),w,SLOT(doLogin()));
    QObject::connect(w,SIGNAL(loginSignal()),w,SLOT(close()));
    QObject::connect(w,SIGNAL(loginSignal()),mw,SLOT(show()));


    */
    mw->show();


    
    return app.exec();
}
