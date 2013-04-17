#include "welcome.h"
#include "mainwindow.h"
#include "connectdb.h"
#include <QtCore>
#include <memory>

//#define PATH_TO_DB "/home/srn/Desktop/ils/ils/ils.sqlite"
#define PATH_TO_DB "/home/srn/Documents/ils/ils.sqlite"


using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Aurora's Integrated Library System");
    QIcon ico;
    ico.addFile(":/res/images/icon.png");
    app.setWindowIcon(ico);



    ConnectDB db(PATH_TO_DB);

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
