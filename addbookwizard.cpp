#include "addbookwizard.h"
#include <QtSql>


// ============== addbookwizard ==================== //
AddBookWizard::AddBookWizard(QWidget *parent) :
    QWizard(parent)
{
    this->addPage(new DetailsPage);
    this->addPage(new FinalPage);
    setModal(true);
    //this->setMaximumHeight(300);
    QWizard::button(QWizard::BackButton)->hide();
   // QWizard::DisabledBackButtonOnLastPage;

}
void AddBookWizard::accept()
{
    QString branches[7]={"COMMON","CIVIL","CSE","ECE","EEE","IT","MECH"};

    int cp = field("copies").toInt();


    QString isbni = field("isbn").toString();
    QString ti = field("title").toString();
    QString ai = field("author").toString();
    QString pubi = field("publisher").toString();
    QString pubdi = field("publishedDate").toString();
    QString ci = field("copies").toString();
    QString bi = branches[field("branch").toInt()];
    //db stuffbooks(title,author,copies,branch)
    QString qr = QString("INSERT INTO books(ISBN, Title, Author, Publisher, PublishedDate, Branch, copies) VALUES('%1','%2','%3','%4','%5','%6','%7')").arg(isbni,ti,ai,pubi,pubdi,bi,ci);
    qDebug() << qr;
    QSqlQuery  q(qr);

    for(int i=0; i<cp; i++){
        //qDebug() << field("book" + QString::number(i+1)).toString();

        QString qqr = "insert into bookNumbers values('" + isbni + "'," + field("book" + QString::number(i+1)).toString()  +")";
        qDebug() << qqr;
        QSqlQuery qq(qqr);

    }


    QDialog::accept();
    this->cleanupPage(0);
    this->cleanupPage(1);
    this->close();
    this->restart();
}

// ========================= detail class ========================== //

DetailsPage::DetailsPage(QWidget *parent)
    : QWizardPage(parent)
{
    numRegex.setPattern("[0-9]+");
    numValidator = new QRegExpValidator(numRegex,this);
    this->setTitle("ADD Book");
    createWidgets();
    createLayouts();
    createConnections();
    registerFields();

}
void DetailsPage::createWidgets()
{
    numRegex.setPattern("[0-9]+");
    numValidator->setRegExp(numRegex);
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

    ISBNEdit->setValidator(numValidator);
    copiesEdit->setValidator(numValidator);

    branchSelector->addItem("COMMON");
    branchSelector->addItem("CIVIL");
    branchSelector->addItem("CSE");
    branchSelector->addItem("ECE");
    branchSelector->addItem("EEE");
    branchSelector->addItem("IT");
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
    //QObject::connect(bookInfoOnline,SIGNAL(dataFetched(QByteArray d)),this,SLOT(getBookInfoOnline()));
    QObject::connect(&bookInfoOnline,SIGNAL(infoFetched()),this,SLOT(processInfo()));

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
void DetailsPage::processInfo()
{
    std::vector<QString> vec;

    vec.clear();
    vec = bookInfoOnline.getInfo();
    for(auto e: vec){
        qDebug() << e;
    }

    titleEdit->setText(vec[0]);
    authorEdit->setText(vec[1]);
    publisherEdit->setText(vec[2]);
    publishedDateEdit->setText(vec[3]);
}

// ============================ final page ========================== //

FinalPage::FinalPage(QWidget *parent)
    : QWizardPage(parent)
{
    numRegex.setPattern("[0-9]+");
    numValidator = new QRegExpValidator(numRegex,this);
    setTitle("add book numbers");
   // qDebug() << field("copies").toInt();
    layout = new QGridLayout;
    this->setLayout(layout);


}
void FinalPage::initializePage()
{
    //clear when back button is pressed for book numbers
    bookNoEdits.clear();
    int copies = field("copies").toInt();


    bookNoEdits.resize(copies);
    for(auto &e : bookNoEdits){
        e = new QLineEdit;
        e->setValidator(numValidator);
    }

    for(int i=0; i<bookNoEdits.size();i++){
        layout->addWidget(new QLabel("Book Number " + QString::number(i+1)),i,0);
        layout->addWidget(bookNoEdits[i],i,1);


        registerField("book" + QString::number(i+1),bookNoEdits[i]);
    }



}


