#include "addbookwizard.h"
#include <QtSql>


// ============== addbookwizard ==================== //
AddBookWizard::AddBookWizard(QWidget *parent) :
    QWizard(parent)
{
    this->addPage(new DetailsPage);
    this->addPage(new FinalPage);
}
void AddBookWizard::accept()
{
    QString branches[6]={"COMMON","CIVIL","CSE","ECE","EEE","MECH"};
    qDebug() << field("book1").toString();

    int cp = field("copies").toInt();

    for(int i=0; i<cp; i++){
        qDebug() << field("book" + QString::number(i+1)).toString();
    }
    QString isbni = field("isbn").toString();
    QString ti = field("title").toString();
    QString ai = field("author").toString();
    QString pubi = field("publisher").toString();
    QString pubdi = field("publishedDate").toString();
    QString ci = field("copies").toString();
    QString bi = branches[field("branch").toInt()];
    //db stuff
    QString qr = QString("INSERT INTO books(title,author,copies,branch) VALUES('%1','%2','%3','%4')").arg(ti,ai,ci,bi);
    qDebug() << qr;
    QSqlQuery  q(qr);

    QDialog::accept();
}

// ========================= detail class ========================== //

DetailsPage::DetailsPage(QWidget *parent)
    : QWizardPage(parent)
{
    this->setTitle("ADD Book");
    createWidgets();
    createLayouts();
    createConnections();
    registerFields();
}
void DetailsPage::createWidgets()
{
    ISBNLabel = new QLabel("ISBN");
    titleLabel = new QLabel("Title");
    authorLabel = new QLabel("Author");
    publisherLabel = new QLabel("Publisher");
    publishedDateLabel = new QLabel("published Date");
    branchLabel = new QLabel("Branch");
    copiesLabel = new QLabel("Copies");

    ISBNEdit = new QLineEdit;
    titleEdit = new QLineEdit;
    authorEdit = new QLineEdit;
    publisherEdit = new QLineEdit;
    publishedDateEdit = new QLineEdit;
    copiesEdit = new QLineEdit;

    branchSelector = new QComboBox;

    fetchInfo = new QPushButton("Fetch info from Online");

    branchSelector->addItem("COMMON");
    branchSelector->addItem("CIVIL");
    branchSelector->addItem("CSE");
    branchSelector->addItem("ECE");
    branchSelector->addItem("EEE");
    branchSelector->addItem("MECH");

}
void DetailsPage::createLayouts()
{
    layout = new QGridLayout;

    layout->addWidget(ISBNLabel,0,0);
    layout->addWidget(ISBNEdit,0,1);
    layout->addWidget(fetchInfo,0,2);
    layout->addWidget(titleLabel,1,0);
    layout->addWidget(titleEdit,1,1);
    layout->addWidget(authorLabel,2,0);
    layout->addWidget(authorEdit,2,1);
    layout->addWidget(publisherLabel,3,0);
    layout->addWidget(publisherEdit,3,1);
    layout->addWidget(publishedDateLabel,4,0);
    layout->addWidget(publishedDateEdit,4,1);
    layout->addWidget(branchLabel,5,0);
    layout->addWidget(branchSelector,5,1);
    layout->addWidget(copiesLabel,6,0);
    layout->addWidget(copiesEdit,6,1);

    this->setLayout(layout);
}
void DetailsPage::createConnections()
{
    QObject::connect(this->fetchInfo,SIGNAL(clicked()),this,SLOT(getBookInfoOnline()));
}
void DetailsPage::registerFields()
{
    registerField("isbn*",ISBNEdit);
    registerField("title*",titleEdit);
    registerField("author*",authorEdit);
    registerField("publisher*",publisherEdit);
    registerField("publishedDate*",publishedDateEdit);
    registerField("branch",branchSelector);
    registerField("copies*",copiesEdit);
}

//slots
void DetailsPage::getBookInfoOnline()
{
    qDebug() << "but pressed and isbn ";
    QString isbn = this->ISBNEdit->text();
    bookInfoOnline.fetchBookInfo(isbn);
}

// ============================ final page ========================== //

FinalPage::FinalPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle("add book numbers");
   // qDebug() << field("copies").toInt();
    layout = new QGridLayout;
    this->setLayout(layout);


}
void FinalPage::initializePage()
{
    int copies = field("copies").toInt();


    for(int i=0; i<copies; i++){
        bookNoEdits.push_back(new QLineEdit);
    }
    for(int i=0; i<bookNoEdits.size();i++){
        layout->addWidget(new QLabel("Book Number " + QString::number(i+1)),i,0);
        layout->addWidget(bookNoEdits[i],i,1);

        registerField("book" + QString::number(i+1),bookNoEdits[i]);
    }



}


