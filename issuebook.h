#ifndef ISSUEBOOK_H
#define ISSUEBOOK_H

#include <QtWidgets>
#include <QtSql>

class IssueBook : public QDialog
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


    explicit IssueBook();
    
signals:
    
public slots:
    void searchStudent(QString s);
    
};

#endif // ISSUEBOOK_H
