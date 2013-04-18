#ifndef BOOKS_H
#define BOOKS_H


#include <QtSql>
#include "wizards/addbookwizard.h" /// includes qtwidgets
#include "wizards/addcopywizard.h"
#include "issuebook.h"
#include "wizards/issuebookwizard.h"
#include "wizards/editbookwizard.h"
#
#include <memory>

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

    QAction *addCopyAction;
    QAction *removeCopyAction;
    QAction *editBookAction;
    QAction *deleteBookAction;
    QAction *issueBookAction;
    QAction *viewSummaryAction;

    AddBookWizard *abw;
    AddCopyWizard *acw;
    EditBookWizard *ebw;
    IssueBook *isbk;
    IssueBookWizard *ibw;

    void createWidgets();
    void createLayout();
    void createConnections();


public:
    explicit Books(QWidget *parent);


    
signals:
    
public slots:
    void filterBooks(QString);
    void searchBooks();
    void searchCompleter();
    void addBook();
    void addCopy();
    void editBook();
    void confirmEditBook();
    void deleteBook();

    void issueBook();
    void confirmIssueBook();

    void viewSummary();
    void enablebut();
};

#endif // BOOKS_H
