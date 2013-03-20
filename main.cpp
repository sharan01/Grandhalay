#include "welcome.h"
#include "mainwindow.h"
#include <QtCore>
#include <QtSql/QtSql>

#define PATH_TO_DB "/home/srn/Documents/ils/ils/ils.sqlite"


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

    if(db.open()){
        qDebug() << "db open";
    }



    Welcome *w = new Welcome;
    MainWindow *mw = new MainWindow;

    /*
    w->show();

    QObject::connect(w->loginButton,SIGNAL(clicked()),w,SLOT(doLogin()));
    QObject::connect(w,SIGNAL(loginSignal()),w,SLOT(close()));
    QObject::connect(w,SIGNAL(loginSignal()),mw,SLOT(show()));


    */
    mw->show();


    
    return app.exec();
}
