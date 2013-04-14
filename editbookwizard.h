#ifndef EDITBOOKWIZARD_H
#define EDITBOOKWIZARD_H

#include <QWizard>
#include <QtWidgets>

class EditBookWizard : public QWizard
{
    Q_OBJECT
public:
    explicit EditBookWizard(std::vector<QString> ,QWidget *parent = 0);
    
signals:
    
public slots:
    
};
// ========================================= //



class EditPage : public QWizardPage
{
    Q_OBJECT
public:
    EditPage(QWidget *parent = 0);
    EditPage(std::vector<QString> , QWidget *parent = 0);
private:
    QLabel isbnLabel;
    QLabel titleLabel;
    QLabel authorLabel;
    QLabel publisherLabel;
    QLabel publishedDateLabel;

    QLineEdit isbnEdit;
    QLineEdit titleEdit;
    QLineEdit authorEdit;
    QLineEdit publisherEdit;
    QLineEdit publishedDateEdit;

    QFormLayout layout;


};

#endif // EDITBOOKWIZARD_H
