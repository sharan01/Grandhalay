#ifndef WELCOME_H
#define WELCOME_H


#include <mainwindow.h>
#include <QtSql/QtSql>

#define PATH_TO_DB "/home/srn/Documents/ils/ils/ils.sqlite"

class Welcome : public QObject
{
    Q_OBJECT

public:
    MainWindow *mw;
    QWidget welcome;


    //layouts
    QGridLayout *wLayout;
    QFormLayout *wFormLayout;

    //widgets
    QLabel *logo;
    QLabel *welcomeMessage;
    QLabel *loginError;
    QLineEdit *nameInput;
    QLineEdit *passInput;

    QPushButton *loginButton;
    QPushButton *aboutButton;


    QSqlDatabase db;

    explicit Welcome();

public slots:
    void doLogin();
    void showAbout();




};

#endif // WELCOME_H
