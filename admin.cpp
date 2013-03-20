#include "admin.h"

Admin::Admin(QWidget *parent) :
    QWidget(parent)
{
    qDebug() << "admin constructed";
    createWidgets();
    createLayout();
    createConnections();
}

void Admin::createWidgets()
{
    changeP = new QPushButton("change password");
    logout = new QPushButton("logout");

    firstW = new QWidget;
    secondW = new QWidget;

    firstW->setFixedWidth(255);

}
void Admin::createLayout()
{

    adminStack = new QStackedLayout;
    firstSL = new QVBoxLayout;
    secondSL = new QVBoxLayout;
    formLayout = new QFormLayout;


    firstSL->addWidget(changeP,Qt::AlignCenter);
    firstSL->addWidget(logout,Qt::AlignCenter);

    firstW->setLayout(firstSL);
    adminStack->addWidget(firstW);
    adminStack->addWidget(new QPushButton("second"));

    this->setLayout(adminStack);

    //adminStack->setCurrentIndex(0);
}
void Admin::createConnections()
{
    QObject::connect(this->changeP,SIGNAL(clicked()),this,SLOT(toFormStack()));
    QObject::connect(this->logout,SIGNAL(clicked()),this,SLOT(doLogout()));
}



// SLOTS
void Admin::toFormStack()
{
    adminStack->setCurrentIndex(1);
}
void Admin::doLogout()
{

    qDebug() << "done destroying";

    qDebug() << this->parentWidget()->parentWidget()->parentWidget();
   this->parentWidget()->parentWidget()->close();
   // this->parentWidget()->parentWidget()->show();


}
