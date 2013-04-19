#ifndef ISSUEBOOKWIZARD_H
#define ISSUEBOOKWIZARD_H

#include <QWizard>
#include <QtWidgets>
#include <QtSql>



// ========== //

class SelectBookNumber : public QWizardPage
{
    Q_OBJECT
private:
    QString bookID; // or book id

    QLabel selectCopyLabel;
    QTableView copyNumbers;

    QVBoxLayout layout;


    QSqlRelationalTableModel model;


    mutable QLineEdit bookNumber; //invisible
public:
    explicit SelectBookNumber(QString, QWidget *parent=0);
    int nextId() const;
signals:

public slots:

};
 // ============= //

class IssueBookPage : public QWizardPage
{
    Q_OBJECT
public:
    QString bookID;
    QLabel bookNo;
    QLabel title;
    QLabel author;
    QLabel copiesLeft;
    QLabel roll;

    QLineEdit ISBNI;
    QLineEdit titleI;
    QLineEdit authorI;
    QLineEdit copiesLeftI;

    mutable QLineEdit studentRollEdit; // invisible

    QLineEdit searchBar;

    QTableView studentsTable;
    QSqlRelationalTableModel model;


    QLabel returnDate;
    QDateEdit returnDateI;



    QGridLayout bookInfoLayout;

    QVBoxLayout issueLayout;
    QHBoxLayout tableLayout;

    QVBoxLayout  mainLayout;


    IssueBookPage(QString,QWidget *parent = 0);
    void createModels();
    void createWidgets();
    void createLayout();
    void createConnections();
    int nextId() const;
private:
    void getBookInfo();

signals:

public slots:
    void searchStudent(QString s);

};
// =============================================================
// =============================================================
// =============================================================

class IssueBookWizard : public QWizard
{
    Q_OBJECT
public:
    IssueBookWizard(QString bkid,QWidget *parent = 0);
    void accept();
private:
    QString bookID;
    SelectBookNumber sbn;
    IssueBookPage ibp;

signals:

public slots:

};

#endif // ISSUEBOOKWIZARD_H
