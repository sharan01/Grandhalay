#include "issuebookwizard.h"

IssueBookWizard::IssueBookWizard(QString bkid, QWidget *parent) :
    QWizard(parent), bookID(bkid), sbn(bkid), ibp(bkid)
{
    addPage(&sbn);
    addPage(&ibp);
    setButtonText(QWizard::FinishButton,"Issue Book");
    accept();

}

void IssueBookWizard::accept()
{


    QString bookNumber = field("bknm").toString();

    int issueDate = QDate::currentDate().toJulianDay();
    int returnDate = field("returnDate").toDate().toJulianDay();

    qDebug() << "book no selected : " << field("bknm").toString();
    qDebug() << "return date : " << field("returnDate").toDate();


        QString memberID;
        qDebug() << "next is clicked";
        QItemSelectionModel *select = ibp.studentsTable.selectionModel();
        QModelIndex i = select->currentIndex();
        QSqlRecord record = ibp.model.record(i.row());
        memberID = record.field("memberID").value().toString();
        qDebug() << "the student selected is " << memberID;

        QString qr = QString("INSERT INTO issue(bookID,bookNo, memberID, issueDate, returnDate) VALUES(%1,%2,%3,%4,%5)").arg(bookID).arg(bookNumber).arg(memberID).arg(issueDate).arg(returnDate);
        QString qr2 = QString("update bookNumbers set issued=1 where bookNo=%1").arg(bookNumber);

        qDebug() << qr;
        qDebug() << qr2;
        QSqlQuery  q(qr);
        QSqlQuery q2(qr2);


QDialog::accept();
}

 // ========= select book number page =============//

SelectBookNumber::SelectBookNumber(QString s, QWidget *parent) :
    QWizardPage(parent), bookID(s)
{
    selectCopyLabel.setText("Select from Available Copies");




    layout.addWidget(&selectCopyLabel);
    layout.addWidget(&copyNumbers);

    setLayout(&layout);
    copyNumbers.setMaximumSize(120,500);

    model.setTable("bookNumbers");
    //model.setFilter("issued=0");
    model.select();
    copyNumbers.setModel(&model);
    copyNumbers.setColumnHidden(0,true);
    copyNumbers.setColumnHidden(1,true);
    copyNumbers.setColumnHidden(3,true);

    model.setFilter("bookID='"+bookID +"'");
    model.setFilter("issued='"+QString::number(0) +"'");


    registerField("bknm",&bookNumber);

    //QObject::connect(this,SIGNAL())


}

int SelectBookNumber::nextId() const
{
    QString booknum;
    qDebug() << "next is clicked";
    QItemSelectionModel *select = copyNumbers.selectionModel();
    QModelIndex i = select->currentIndex();
    QSqlRecord record = model.record(i.row());
    booknum = record.field("bookNo").value().toString();
    qDebug() << booknum;

    bookNumber.setText(booknum);


    return 1;
}


// =============== issue book page ============= //

IssueBookPage::IssueBookPage(QString s, QWidget *parent) :
    QWizardPage(parent), bookID(s)

{
    qDebug() << "issuebookpage constructed";
    createModels();
    createWidgets();
    createLayout();






    ISBNI.setDisabled(true);
    titleI.setDisabled(true);
    authorI.setDisabled(true);
    copiesLeftI.setDisabled(true);
    returnDateI.setDate(QDate::currentDate());
    searchBar.setPlaceholderText("search");


    studentsTable.setModel(&model);
    studentsTable.setColumnHidden(1,true);
    studentsTable.setSortingEnabled(true);
    studentsTable.setSelectionBehavior(QAbstractItemView::SelectRows);
    studentsTable.setColumnHidden(0,true);


    getBookInfo();




    registerField("returnDate",&returnDateI);




    QObject::connect(&searchBar,SIGNAL(textChanged(QString)),this,SLOT(searchStudent(QString)));
}

void IssueBookPage::createModels()
{

    model.setTable("members");
    model.select();

}
void IssueBookPage::createWidgets()
{
    bookNo.setText("ISBN");
    title.setText("Title");
    author.setText("Author");
    copiesLeft.setText("copies left");
    roll.setText("Roll No");




    returnDate.setText("Return Date");

}
void IssueBookPage::createLayout()
{


    bookInfoLayout.addWidget(&bookNo,0,0,1,1);
    bookInfoLayout.addWidget(&ISBNI,0,1,1,1);
    bookInfoLayout.addWidget(&title,0,2,1,1);
    bookInfoLayout.addWidget(&titleI,0,3,1,1);
    bookInfoLayout.addWidget(&author,1,0,1,1);
    bookInfoLayout.addWidget(&authorI,1,1,1,1);
    bookInfoLayout.addWidget(&copiesLeft,1,2,1,1);
    bookInfoLayout.addWidget(&copiesLeftI,1,3,1,1);
    bookInfoLayout.addWidget(&roll,2,0,1,1);
    bookInfoLayout.addWidget(&searchBar,2,1,1,1);

    issueLayout.addWidget(&returnDate,0,Qt::AlignBottom);
    issueLayout.addWidget(&returnDateI);

    tableLayout.addWidget(&studentsTable);
    tableLayout.addLayout(&issueLayout);

    mainLayout.addLayout(&bookInfoLayout);
    mainLayout.addLayout(&tableLayout);

    setLayout(&mainLayout);
}


void IssueBookPage::getBookInfo()
{
    QSqlQuery qry;
    QString qq = "SELECT * FROM books WHERE bookID =" + bookID;
    qDebug() << qq;
    if(qry.exec(qq)){
        if(qry.next()){

            qDebug() << "query has nxt";
            //isbn
            ISBNI.setText(qry.value("ISBN").toString());
            titleI.setText(qry.value("Title").toString());
            authorI.setText(qry.value("Author").toString());
            //copiesLeftI->setDisabled(true);


            //qDebug() << qry.value(0).toString();

        }else{
            qDebug() << "query retirned no BookId";
        }
    }else{
        qDebug() << "query error";

    }

}

int IssueBookPage::nextId() const
{
    qDebug() << "finished clicked issue book wiz";
    return -1;

}
// slots ======================
void IssueBookPage::searchStudent(QString s)
{
    model.setFilter("Roll LIKE '%"+s+"%'");
    qDebug() << "rollNo LIKE '%"+s+"%'";
}
