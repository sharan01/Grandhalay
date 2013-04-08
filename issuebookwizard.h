#ifndef ISSUEBOOKWIZARD_H
#define ISSUEBOOKWIZARD_H

#include <QWizard>
#include <QtWidgets>
#include <QtSql>
class SelectBookNumber;
class IssueBookWizard : public QWizard
{
    Q_OBJECT
public:
    explicit IssueBookWizard(QWidget *parent = 0);
    void accept();
    SelectBookNumber *sbn;
    
signals:
    
public slots:

};

// ========== //

class SelectBookNumber : public QWizardPage
{
    Q_OBJECT
private:
    QString ISBN; // or book id

    QLabel *selectCopyLabel;
    QTableView *copyNumbers;

    QVBoxLayout *layout;


    QSqlRelationalTableModel *model;
public:
    explicit SelectBookNumber(QWidget *parent=0);
    void setISBN(QString); // or bookid
signals:

public slots:

};
 // ============= //

class IssueBookPage : public QWizardPage
{
    Q_OBJECT
public:
    int bookID;
    QLabel *bookNo;
    QLabel *title;
    QLabel *author;
    QLabel *copiesLeft;
    QLabel *roll;

    QLineEdit *bookNoI;
    QLineEdit *titleI;
    QLineEdit *authorI;
    QLineEdit *copiesLeftI;

    QLineEdit *searchBar;

    QTableView *studentsTable;
    QSqlRelationalTableModel *model;


    QLabel *returnDate;
    QDateEdit *returnDateI;

    QPushButton *issueButton;


    QGridLayout *bookInfoLayout;

    QVBoxLayout *issueLayout;
    QHBoxLayout *tableLayout;

    QVBoxLayout  *mainLayout;


    explicit IssueBookPage();
    void createModels();
    void createWidgets();
    void createLayout();
    void createConnections();

signals:

public slots:
    void searchStudent(QString s);

};

#endif // ISSUEBOOKWIZARD_H
