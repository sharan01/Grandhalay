#ifndef BOOKS_H
#define BOOKS_H

#include <QWidget>
#include <QtGui>
#include <QtSql>
#include "addbook.h"

class Books : public QWidget
{
    Q_OBJECT
private:
    QGridLayout *searchLayout;
    QHBoxLayout *bookTopLayout;
    QVBoxLayout *bookLayout;


    //top widgets
    QComboBox *branchSelector;
    QPushButton *addBookButton;
    QLineEdit *searchBar;
    QRadioButton *searchRadioTitle;
    QRadioButton *searchRadioAuthor;
    QPushButton *searchButton;

    QTableView *booksTable;


    QSqlRelationalTableModel *model;
    QSortFilterProxyModel *proxyModel;

    QCompleter *completer;

    QAction *addBookAction;

    AddBook *adbk;



public:
    explicit Books();


    
signals:
    
public slots:
    void filterBooks(QString);
    void searchBooks();
    void searchCompleter();
    void context();
    void addBook();
    void confirmAddBook();
};

#endif // BOOKS_H
