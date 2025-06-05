#include "welcome.h"
#include "mainwindow.h"
#include "connectdb.h"
#include <QtCore>
#include <memory>




using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Aurora's Integrated Library System");
    QIcon ico;
    ico.addFile(":/res/images/icon.png");
    app.setWindowIcon(ico);



    QString dbPath = (argc > 1) ? argv[1] : QString("ils.sqlite");
    ConnectDB db(dbPath);

    Welcome w;
    MainWindow mw;

    /*
    w->show();

    QObject::connect(w->loginButton,SIGNAL(clicked()),w,SLOT(doLogin()));
    QObject::connect(w,SIGNAL(loginSignal()),w,SLOT(close()));
    QObject::connect(w,SIGNAL(loginSignal()),mw,SLOT(show()));


    */
    mw.show();
    //mw->showMaximized();
    //mw




    return app.exec();
}
