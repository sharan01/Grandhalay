#ifndef ISSUEBOOKWIZARD_H
#define ISSUEBOOKWIZARD_H

#include <QWizard>
#include <QtWidgets>
#include <QtSql>
class IssueBookWizard : public QWizard
{
    Q_OBJECT
public:
    explicit IssueBookWizard(QWidget *parent = 0);
    void accept();
    
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
    QListView *copyNumbers;

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
    explicit IssueBookPage(QWidget *parent=0);

signals:

public slots:

};

#endif // ISSUEBOOKWIZARD_H
