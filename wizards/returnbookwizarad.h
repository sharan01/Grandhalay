#ifndef RETURNBOOKWIZARAD_H
#define RETURNBOOKWIZARAD_H

#include <QWizard>
#include <QtWidgets>
#include <QtSql>



class SelectBookPage : public QWizardPage
{
    Q_OBJECT
public:
    explicit SelectBookPage(QWidget *parent = 0);
    void getStudentInfo();
private:
    QString bookID;
    QLabel rollLabel;
    QLabel nameLabel;
    QLabel branchLabel;


    QLabel booksTaken;

    QLineEdit roll;
    QLineEdit name;
    QLineEdit branch;

    mutable QLineEdit studentRollEdit; // invisible


    QTableView issuedBooksTable;
    QSqlRelationalTableModel model;




    QGridLayout layout;


signals:

public slots:
};
// =========================== //
class ReturnFinalPage : public QWizardPage
{
    Q_OBJECT
public:
    explicit ReturnFinalPage(QWidget *parent = 0);

signals:

public slots:
};


/// ======================//
class ReturnBookWizarad : public QWizard
{
    Q_OBJECT
public:
    explicit ReturnBookWizarad(QWidget *parent = 0);
    void accept();
    
signals:
    
public slots:
    
};

#endif // RETURNBOOKWIZARAD_H
