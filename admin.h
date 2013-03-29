#ifndef ADMIN_H
#define ADMIN_H

#include <QtWidgets>


class Admin : public QWidget
{
    Q_OBJECT
private:
    QPushButton *changeP;
    QPushButton *logout;

    QWidget *firstW;
    QWidget *secondW;
    QStackedLayout *adminStack;
    QVBoxLayout *firstSL;
    QVBoxLayout *secondSL;
    QFormLayout *formLayout;

    void createWidgets();
    void createLayout();
    void createConnections();

public:
    explicit Admin(QWidget *parent = 0);





    
signals:
    
public slots:
    void toFormStack();
    void doLogout();
};

#endif // ADMIN_H
