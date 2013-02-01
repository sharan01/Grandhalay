#include "welcome.h"
#include <QDebug>

Welcome::Welcome()
{


    //layouts
    welcome.setWindowTitle("Aurora's Integrated Library System");
    wLayout = new QGridLayout;
    wFormLayout = new QFormLayout;

    //widgets
    logo = new QLabel("<img src='logo.png'/>");
    welcomeMessage = new QLabel("Welcome to Aurora's\nIntegrated Library System");
    welcomeMessage->setStyleSheet("font-size:24px;");

    loginError = new QLabel();
    nameInput = new QLineEdit;
    passInput = new QLineEdit;

    loginButton = new QPushButton("Login");
    aboutButton = new QPushButton("About");



    wFormLayout->addRow("Name :", nameInput);
    wFormLayout->addRow("Password :", passInput);

    wLayout->addWidget(logo,0,0,1,1);
    wLayout->addWidget(welcomeMessage,0,1,1,4);
    wLayout->addLayout(wFormLayout,1,1,1,1);
    wLayout->addWidget(aboutButton,3,0,1,1);
    wLayout->addWidget(loginButton,3,1,1,1);
    wLayout->addWidget(loginError,4,1,1,1);

    //
    db = QSqlDatabase::addDatabase("QSQLITE"); //  delete in destructor
    db.setDatabaseName(PATH_TO_DB);
    if(db.open()){
        printf("open");
    }




    welcome.setLayout(wLayout);

    //temporary
   //welcome.show();
   mw = new MainWindow;


    QObject::connect(loginButton,SIGNAL(clicked()),this,SLOT(doLogin()));

    QObject::connect(aboutButton,SIGNAL(clicked()),this,SLOT(showAbout()));

}
void Welcome::doLogin()
{
    QSqlQuery qry;
    QString qq = "SELECT name, pass FROM users WHERE name = '" + nameInput->text() +"' AND pass = '" + passInput->text() +"'";
    qDebug() << qq;
    QString q = "SELECT * FROM users WHERE id=1";

    if(db.open()){
        if(qry.exec(qq)){
            if(qry.next()){
//                QString name = qry.value(0).toString();
//                QString pass = qry.value(1).toString();
                welcome.hide();
                mw = new MainWindow;
            }else{
                loginError->setText("Incorrect login credentials");
                loginError->setStyleSheet("color:red;");
            }
        }else{
            qDebug() << "query error";

        }
    }
   else{
        loginError->setText("Unable to connect to the Database");
        loginError->setStyleSheet("color:red;");
    }


}
void Welcome::showAbout()
{
    QMessageBox msgBox;
    msgBox.setText("<img src='logo.png'/> <p>Aurora's Integrated Library System \ndeveloped by .....</p>");
    msgBox.exec();
}

