#include "addbookwizard.h"
#include <QtSql>


// ============== addbookwizard ==================== //
AddBookWizard::AddBookWizard(QWidget *parent) :
    QWizard(parent)
{
    qDebug() << "Add Book Wizard constructed";
    addPage(&dp);
    addPage(&fp);
    setModal(true);
}

AddBookWizard::~AddBookWizard()
{
    qDebug() << "Add Book Wizard destructed";
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

    QString bookid = getBookId(isbni);
    for(int i=0; i<cp; i++){
        //qDebug() << field("book" + QString::number(i+1)).toString();

        QString qqr = QString("INSERT INTO bookNumbers(bookID,ISBN,bookNo) VALUES(%1,'%2','%3')").arg(bookid,isbni,field("book" + QString::number(i+1)).toString());
        qDebug() << qqr;
        QSqlQuery qq(qqr);

    }


    QDialog::accept();
    this->cleanupPage(0);
    this->cleanupPage(1);
    this->close();
    this->restart();
}
QString AddBookWizard::getBookId(QString isbn)
{
    QString BookID;
    QSqlQuery qry;
    QString qq = "SELECT bookID FROM books WHERE ISBN = '" + isbn +"'";
    qDebug() << qq;
    if(qry.exec(qq)){
        if(qry.next()){
            // credentials are present in db
            qDebug() << "query has nxt";

            qDebug() << qry.value(0).toString();
            BookID = qry.value(0).toString();

        }else{
            qDebug() << "query retirned no BookId";
        }
    }else{
        qDebug() << "query error";

    }
   return BookID;

}

// ========================= detail class ========================== //

DetailsPage::DetailsPage(QWidget *parent)
    : QWizardPage(parent)
{
    numRegex.setPattern("[0-9]+");
    numValidator.setRegExp(numRegex);
    this->setTitle("ADD Book");
    createWidgets();
    createLayouts();
    createConnections();
    registerFields();

}
void DetailsPage::createWidgets()
{

    ISBNLabel.setText("ISBN");
    titleLabel.setText("Title");
    authorLabel.setText("Author");
    publisherLabel.setText("Publisher");
    publishedDateLabel.setText("Publisher Date");
    branchLabel.setText("Branch");
    copiesLabel.setText("Copies");

    fetchInfo.setText("Fetch Info from online");

    ISBNEdit.setValidator(&numValidator);
    copiesEdit.setValidator(&numValidator);

    branchSelector.addItem("COMMON");
    branchSelector.addItem("CIVIL");
    branchSelector.addItem("CSE");
    branchSelector.addItem("ECE");
    branchSelector.addItem("EEE");
    branchSelector.addItem("IT");
    branchSelector.addItem("MECH");

}
void DetailsPage::createLayouts()
{


    layout.addWidget(&ISBNLabel,0,0);
    layout.addWidget(&ISBNEdit,0,1);
    layout.addWidget(&fetchInfo,0,2);
    layout.addWidget(&titleLabel,1,0);
    layout.addWidget(&titleEdit,1,1);
    layout.addWidget(&authorLabel,2,0);
    layout.addWidget(&authorEdit,2,1);
    layout.addWidget(&publisherLabel,3,0);
    layout.addWidget(&publisherEdit,3,1);
    layout.addWidget(&publishedDateLabel,4,0);
    layout.addWidget(&publishedDateEdit,4,1);
    layout.addWidget(&branchLabel,5,0);
    layout.addWidget(&branchSelector,5,1);
    layout.addWidget(&copiesLabel,6,0);
    layout.addWidget(&copiesEdit,6,1);


    this->setLayout(&layout);
}
void DetailsPage::createConnections()
{
    QObject::connect(&fetchInfo,SIGNAL(clicked()),this,SLOT(getBookInfoOnline()));
    //QObject::connect(bookInfoOnline,SIGNAL(dataFetched(QByteArray d)),this,SLOT(getBookInfoOnline()));
    QObject::connect(&bookInfoOnline,SIGNAL(infoFetched()),this,SLOT(processInfo()));

}
void DetailsPage::registerFields()
{
    registerField("isbn*",&ISBNEdit);
    registerField("title*",&titleEdit);
    registerField("author*",&authorEdit);
    registerField("publisher*",&publisherEdit);
    registerField("publishedDate*",&publishedDateEdit);
    registerField("branch",&branchSelector);
    registerField("copies*",&copiesEdit);
}

//slots
void DetailsPage::getBookInfoOnline()
{
    qDebug() << "but pressed and isbn ";
    QString isbn = ISBNEdit.text();
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

    titleEdit.setText(vec[0]);
    authorEdit.setText(vec[1]);
    publisherEdit.setText(vec[2]);
    publishedDateEdit.setText(vec[3]);
}

// ============================ final page ========================== //

FinalPage::FinalPage(QWidget *parent)
    : QWizardPage(parent)
{
    qDebug() << "Final Page constructed";
    setTitle("add book numbers");
    setLayout(&layout);

    numRegex.setPattern("[0-9]+");
    numValidator.setRegExp(numRegex);

}

FinalPage::~FinalPage()
{
    qDebug() << "Final Page destructed";
    for(auto &e: bookNoEdits){
        delete e;
    }
    for(auto &e: bookNoLabels){
        delete e;
    }

}

void FinalPage::initializePage()
{

    int copies = field("copies").toInt();


    bookNoLabels.resize(copies);
    bookNoEdits.resize(copies);

    for(int i=0; i<copies; i++){
        bookNoLabels[i] = new QLabel("Book Number " + QString::number(i+1));
        bookNoEdits[i] = new QLineEdit;
        bookNoEdits[i]->setValidator(&numValidator);

        layout.addWidget(bookNoLabels[i],i,0);
        layout.addWidget(bookNoEdits[i],i,1);


        registerField("book" + QString::number(i+1),bookNoEdits[i]);

    }



}
