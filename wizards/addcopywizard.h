#ifndef ADDCOPYWIZARD_H
#define ADDCOPYWIZARD_H

#include <QtWidgets>
#include <QWizard>
#include <QtSql>




// ================= //
class NumPage : public QWizardPage
{
    Q_OBJECT
public:
    NumPage(QWidget *parent = 0);

private:
    QLineEdit noCopies;

    QFormLayout layout;
};
// ===================== //

class CopyFinalPage : public QWizardPage
{
    Q_OBJECT
public:
    CopyFinalPage(QWidget *parent = 0);
    ~CopyFinalPage();
    void initializePage();
private:
    std::vector<QLineEdit *> bookNoVector;

    QFormLayout layout;
};



// ======================================= //
class AddCopyWizard : public QWizard
{
    Q_OBJECT
public:
    AddCopyWizard(QWidget *parent = 0);
    AddCopyWizard(QString bookID,QString ISBN, QWidget *parent = 0);
    void accept();
private:
    NumPage np;
    CopyFinalPage cfp;

    QString w_bookID;
    QString w_ISBN;


signals:

public slots:

};
#endif // ADDCOPYWIZARD_H
