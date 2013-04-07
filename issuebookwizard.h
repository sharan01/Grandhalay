/*#ifndef ISSUEBOOKWIZARD_H
#define ISSUEBOOKWIZARD_H

#include <QWizard>
#include <QtWidgets>

class IssueBookWizard : public QWizard
{
    Q_OBJECT
public:
    explicit IssueBookWizard(QWidget *parent = 0);
    
signals:
    
public slots:

};

// ========== //

class selectBookNumber : public QWizardPage
{
    Q_OBJECT
private:
    QString ISBN; // or book id

    QLabel *selectCopyLabel;
    QListView copyNumbers;

    QListModel *model;
public:
    explicit selectBookNumber(QWidget *parent=0);
    void setISBN(QString); // or bookid
signals:

public slots:

};
 // ============= //

class IssueBookPage : public QWizardPage
{
    Q_OBJECT
public:
    explicit selectBookNumber(QWidget *parent=0);

signals:

public slots:

};

#endif // ISSUEBOOKWIZARD_H
*/
