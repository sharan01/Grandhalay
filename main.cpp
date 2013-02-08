#include "welcome.h"
#include <QtCore>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Aurora's Integrates Library System");
    QIcon ico;
    ico.addFile("icon.png");
    app.setWindowIcon(ico);


    Welcome w;





    
    return app.exec();
}
