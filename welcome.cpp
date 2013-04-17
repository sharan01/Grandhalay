/*
 *map enter key to login button
 */
#include "welcome.h"
#include <QDebug>

Welcome::Welcome(QWidget *parent) :
    QWidget(parent)
{
    qDebug() << "welcome constructed";

    createResources();
    createWidgets();
    createLayout();
    createConnections();




}
void Welcome::createResources()
{
    lg.load(":/res/images/logo.png");
    ico.load(":/res/images/icon.png");
}
void Welcome::createWidgets()
{

    logo = new QLabel;
    welcomeMessage = new QLabel("Welcome to Aurora's\nIntegrated Library System");

    loginError = new QLabel;
    nameInput = new QLineEdit;
    passInput = new QLineEdit;

    loginButton = new QPushButton("Login");
    aboutButton = new QPushButton("About");

    logo->setPixmap(lg);
    welcomeMessage->setStyleSheet("font-size:24px;");
    this->setWindowTitle("Aurora's Integrated Library System");

}
void Welcome::createLayout()
{
    wLayout = new QGridLayout;
    wFormLayout = new QFormLayout;

    wFormLayout->addRow("Name :", nameInput);
    wFormLayout->addRow("Password :", passInput);

    wLayout->addWidget(logo,0,0,1,1);
    wLayout->addWidget(welcomeMessage,0,1,1,4);
    wLayout->addLayout(wFormLayout,1,1,1,1);
    wLayout->addWidget(aboutButton,3,0,1,1);
    wLayout->addWidget(loginButton,3,1,1,1);
    wLayout->addWidget(loginError,4,1,1,1);

    this->setLayout(wLayout);


}
void Welcome::createConnections()
{
    QObject::connect(aboutButton,SIGNAL(clicked()),this,SLOT(showAbout()));
}

// =============== SLOTS ================ //
void Welcome::doLogin()
{
    QSqlQuery qry;
    QString qq = "SELECT name, pass FROM users WHERE name = '" + nameInput->text() +"' AND pass = '" + passInput->text() +"'";
    qDebug() << qq;
    QString q = "SELECT * FROM users WHERE id=1";

        if(qry.exec(qq)){
            if(qry.next()){
                // credentials are present in db

                QString name = qry.value(0).toString();
                QString pass = qry.value(1).toString();

                // emit signal here
                emit loginSignal();

                //welcome.hide();
                //mw = new MainWindow;
            }else{
                loginError->setText("Incorrect login credentials");
                loginError->setStyleSheet("color:red;");
            }
        }else{
            qDebug() << "query error";

        }
}
void Welcome::showAbout()
{
    QMessageBox msgBox;
    msgBox.setIconPixmap(ico);
    msgBox.setWindowTitle("About ILS");
    msgBox.setText("<p>Integrated Library System<br><br>Developed by <br><br>K Niranjan<br>S Sharan<br>V Rahul</p>");
    msgBox.exec();
}



