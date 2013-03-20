#ifndef WELCOME_H
#define WELCOME_H


#include <mainwindow.h>




class Welcome : public QWidget
{
    Q_OBJECT

private:
    //widgets
    QPixmap lg;
    QPixmap ico;
    QLabel *logo;
    QLabel *welcomeMessage;
    QLabel *loginError;
    QLineEdit *nameInput;
    QLineEdit *passInput;
    QPushButton *aboutButton;

    //layouts
    QGridLayout *wLayout;
    QFormLayout *wFormLayout;

    void createResources();
    void createWidgets();
    void createLayout();
    void createConnections();
public:
    QPushButton *loginButton;// public to use in connect main

    explicit Welcome(QWidget *parent = 0);
signals:
    void loginSignal();
public slots:
    void doLogin();
    void showAbout();

};

#endif // WELCOME_H
