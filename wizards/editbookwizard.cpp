#include "editbookwizard.h"

EditBookWizard::EditBookWizard(std::vector<QString> s,QWidget *parent) :
     QWizard(parent), ep(s,this)
{
    bookID = s[0];
    addPage(&ep);
    qDebug() << s[3];
}
void EditBookWizard::accept()
{
    QString branches[7]={"COMMON","CIVIL","CSE","ECE","EEE","IT","MECH"};

    QString isbni = field("isbn").toString();
    QString ti = field("title").toString();
    QString ai = field("author").toString();
    QString pubi = field("publisher").toString();
    QString pubdi = field("publishedDate").toString();
    QString bi = branches[field("branch").toInt()];

    QString qr = QString("UPDATE books SET ISBN='%1', Title='%2',Author='%3',Publisher='%4',PublishedDate='%5',Branch='%6' WHERE bookID=%7").arg(isbni,ti,ai,pubi,pubdi,bi,bookID);
    qDebug() << qr;

    QSqlQuery q(qr);

    q.exec();

    QDialog::accept();

}

//===================================================///

EditPage::EditPage(QWidget *parent) :
    QWizardPage(parent)
{
    qDebug() << "empty cosntructor editpage";
}


EditPage::EditPage(std::vector<QString> s,QWidget *parent) :
    QWizardPage(parent)
{
    branchSelector.addItem("COMMON");
    branchSelector.addItem("CIVIL");
    branchSelector.addItem("CSE");
    branchSelector.addItem("ECE");
    branchSelector.addItem("EEE");
    branchSelector.addItem("IT");
    branchSelector.addItem("MECH");

    isbnEdit.setText(s[1]);
    titleEdit.setText(s[2]);
    authorEdit.setText(s[3]);
    publisherEdit.setText(s[4]);
    publishedDateEdit.setText(s[5]);
    branchSelector.setCurrentIndex(branchSelector.findText(s[6]));


    // create layout ==================================
    layout.addRow("ISBN",&isbnEdit);
    layout.addRow("Title",&titleEdit);
    layout.addRow("Author",&authorEdit);
    layout.addRow("Publisher",&publisherEdit);
    layout.addRow("Publisher Date",&publishedDateEdit);
    layout.addRow("Branch",&branchSelector);

    setLayout(&layout);

    registerField("isbn",&isbnEdit);
    registerField("title",&titleEdit);
    registerField("author",&authorEdit);
    registerField("publisher",&publisherEdit);
    registerField("publishedDate",&publishedDateEdit);


}
