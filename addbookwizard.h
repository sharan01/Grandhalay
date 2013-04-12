#ifndef ADDBOOKWIZARD_H
#define ADDBOOKWIZARD_H

#include <vector>
#include <QWizard>
#include <QRegExp>
#include <QRegExpValidator>
#include <QtWidgets>
#include "bookinfoonline.h"

//class DetailsPage;
//class FinalPage;


// first page
class DetailsPage : public QWizardPage
{
    Q_OBJECT

public:
    DetailsPage(QWidget *parent = 0);
public slots:
     void getBookInfoOnline();
     void processInfo();

private:
    QRegExp numRegex;
    QRegExpValidator numValidator;
    QLabel ISBNLabel;
    QLabel titleLabel;
    QLabel authorLabel;
    QLabel publisherLabel;
    QLabel publishedDateLabel;
    QLabel branchLabel;
    QLabel copiesLabel;

    QLineEdit ISBNEdit;
    QLineEdit titleEdit;
    QLineEdit authorEdit;
    QLineEdit publisherEdit;
    QLineEdit publishedDateEdit;
    //branch combo box
    QLineEdit copiesEdit;

    QComboBox branchSelector;

    QPushButton fetchInfo;

    QGridLayout layout;

    BookInfoOnline bookInfoOnline;

    void createWidgets();
    void createLayouts();
    void createConnections();

    void registerFields();
};



class FinalPage : public QWizardPage
{
    Q_OBJECT
public:
    FinalPage(QWidget *parent = 0);
    ~FinalPage();

    void initializePage();

public slots:

private:
    QRegExp numRegex;
    QRegExpValidator numValidator;
    std::vector<QLineEdit *> bookNoEdits;
    std::vector<QLabel *> bookNoLabels;
    QGridLayout layout;

};

// main qwizard ===========================================


class AddBookWizard : public QWizard
{
    Q_OBJECT
public:
    explicit AddBookWizard(QWidget *parent = 0);
    ~AddBookWizard();

    void accept();
    DetailsPage dp;
    FinalPage fp;
signals:

public slots:



};

#endif // ADDBOOKWIZARD_H
