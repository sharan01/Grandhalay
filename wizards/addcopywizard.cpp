#include "addcopywizard.h"

AddCopyWizard::AddCopyWizard(QString bookID, QString ISBN, QWidget *parent) :
    QWizard(parent), w_bookID(bookID), w_ISBN(ISBN)
{
    qDebug() << "addcopywizard constructed with bookId  " << bookID;

    addPage(&np);
    addPage(&cfp);





}
AddCopyWizard::AddCopyWizard(QWidget *parent) :
    QWizard(parent)
{
}
void AddCopyWizard::accept()
{
    int copies = field("noCopies").toInt();
    QString q;
    QSqlQuery query;
    for(int i=0; i<copies; i++){
        q = QString("INSERT INTO bookNumbers VALUES(%1,'%2','%3')").arg(w_bookID,w_ISBN,field("book" + QString::number(i+1)).toString());
        query.exec(q);

        qDebug() << q;
    }


    QDialog::accept();
}



//==================== page ====================== //
NumPage::NumPage(QWidget *parent) :
    QWizardPage(parent)
{
    layout.addRow("Number of copies to add",&noCopies);

    setLayout(&layout);


    registerField("noCopies",&noCopies);
}
// ==================================================== //
CopyFinalPage::CopyFinalPage(QWidget *parent) :
    QWizardPage(parent)
{
    setLayout(&layout);
}
CopyFinalPage::~CopyFinalPage()
{
    for(auto &e : bookNoVector){
        delete e;
    }
}

void CopyFinalPage::initializePage()
{
    int copies = field("noCopies").toInt();

    bookNoVector.resize(copies);

    for(int i=0; i<copies; i++){
        bookNoVector[i] = new QLineEdit;
        layout.addRow("Book Number " + QString::number(i+1),bookNoVector[i]);
        registerField("book" + QString::number(i+1),bookNoVector[i]);
    }
}
