#ifndef EDITBOOKWIZARD_H
#define EDITBOOKWIZARD_H

#include <QWizard>
#include <QtWidgets>
#include <QtSql>

class EditPage : public QWizardPage
{
    Q_OBJECT
public:
    EditPage(QWidget *parent = 0);
    EditPage(std::vector<QString> , QWidget *parent = 0);
private:
    QLineEdit isbnEdit;
    QLineEdit titleEdit;
    QLineEdit authorEdit;
    QLineEdit publisherEdit;
    QLineEdit publishedDateEdit;
    QComboBox branchSelector;

    QFormLayout layout;






};
// ========================================= //
class EditBookWizard : public QWizard
{
    Q_OBJECT
public:
    EditBookWizard(std::vector<QString>, QWidget *parent = 0);

    void accept();


private:
    EditPage ep;
    QString bookID;

    
signals:
    
public slots:
    
};
// ========================================= //





#endif // EDITBOOKWIZARD_H
