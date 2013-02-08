

#include "issuebook.h"

IssueBook::IssueBook()
{
    bookNo = new QLabel("ISBN");
    title = new QLabel("Title");
    author = new QLabel("Author");
    copiesLeft = new QLabel("copies left");
    roll = new QLabel("Roll No");

    bookNoI = new QLineEdit;
    titleI = new QLineEdit;
    authorI = new QLineEdit;
    copiesLeftI = new QLineEdit;


    searchBar = new QLineEdit;


    studentsTable = new QTableView;
    model = new QSqlRelationalTableModel;



    returnDate = new QLabel("Return Date");
    returnDateI = new QDateEdit();

    issueButton = new QPushButton("issue book");


    bookInfoLayout = new QGridLayout;
    issueLayout = new QVBoxLayout;
    tableLayout = new QHBoxLayout;

    mainLayout = new QVBoxLayout;

    bookNoI->setDisabled(true);
    titleI->setDisabled(true);
    authorI->setDisabled(true);
    copiesLeftI->setDisabled(true);
    returnDateI->setDate(QDate::currentDate());
    searchBar->setPlaceholderText("search");
    model->setTable("students");
    model->select();

    studentsTable->setModel(model);
    studentsTable->setColumnHidden(0,true);
    studentsTable->setSortingEnabled(true);





    bookInfoLayout->addWidget(bookNo,0,0,1,1);
    bookInfoLayout->addWidget(bookNoI,0,1,1,1);
    bookInfoLayout->addWidget(title,0,2,1,1);
    bookInfoLayout->addWidget(titleI,0,3,1,1);
    bookInfoLayout->addWidget(author,1,0,1,1);
    bookInfoLayout->addWidget(authorI,1,1,1,1);
    bookInfoLayout->addWidget(copiesLeft,1,2,1,1);
    bookInfoLayout->addWidget(copiesLeftI,1,3,1,1);
    bookInfoLayout->addWidget(roll,2,0,1,1);
    bookInfoLayout->addWidget(searchBar,2,1,1,1);

    issueLayout->addWidget(returnDate,0,Qt::AlignBottom);
    issueLayout->addWidget(returnDateI);
    issueLayout->addWidget(issueButton);

    tableLayout->addWidget(studentsTable);
    tableLayout->addLayout(issueLayout);

    mainLayout->addLayout(bookInfoLayout);
    mainLayout->addLayout(tableLayout);

    this->setLayout(mainLayout);

    qDebug() << "issuebok constructed";

    QObject::connect(this->searchBar,SIGNAL(textChanged(QString)),this,SLOT(searchStudent(QString)));

}

void IssueBook::searchStudent(QString s)
{
    model->setFilter("rollNo LIKE '%"+s+"%'");
}
