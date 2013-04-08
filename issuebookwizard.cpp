#include "issuebookwizard.h"

IssueBookWizard::IssueBookWizard(QWidget *parent) :
    QWizard(parent)
{
    sbn = new SelectBookNumber(this);
    addPage(sbn);
    addPage(new IssueBookPage);
    setButtonText(QWizard::FinishButton,"Issue Book");
    accept();

}

void IssueBookWizard::accept()
{
    QDialog::accept();
    qDebug () << field("qq");

    this->restart();
}

 // ========= select book number page =============//

SelectBookNumber::SelectBookNumber(QWidget *parent) :
    QWizardPage(parent)
{
    selectCopyLabel = new QLabel("Select from Available Copies");
    copyNumbers = new QTableView;
    layout = new QVBoxLayout;

    model = new QSqlRelationalTableModel;

    layout->addWidget(selectCopyLabel);
    layout->addWidget(copyNumbers);

    setLayout(layout);
    copyNumbers->setMaximumSize(120,500);

    model->setTable("bookNumbers");
    model->select();
    copyNumbers->setModel(model);
    copyNumbers->setColumnHidden(0,true);


    registerField("qq",copyNumbers);
}
void SelectBookNumber::setISBN(QString s)
{
    ISBN = s;
    model->setFilter("ISBN='"+s +"'");


}


// =============== issue book page ============= //

IssueBookPage::IssueBookPage()

{
    qDebug() << "issuebookpage constructed";
    createModels();
    createWidgets();

    issueButton = new QPushButton("issue book");
    // temp
    issueButton->setDisabled(true);




    bookNoI->setDisabled(true);
    titleI->setDisabled(true);
    authorI->setDisabled(true);
    copiesLeftI->setDisabled(true);
    returnDateI->setDate(QDate::currentDate());
    searchBar->setPlaceholderText("search");


    studentsTable->setModel(model);
    studentsTable->setColumnHidden(1,true);
    studentsTable->setSortingEnabled(true);
    studentsTable->setSelectionBehavior(QAbstractItemView::SelectRows);









    QObject::connect(this->searchBar,SIGNAL(textChanged(QString)),this,SLOT(searchStudent(QString)));
}

void IssueBookPage::createModels()
{
    model = new QSqlRelationalTableModel;
    model->setTable("students");
    model->select();

}
void IssueBookPage::createWidgets()
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




    returnDate = new QLabel("Return Date");
    returnDateI = new QDateEdit();

}
void IssueBookPage::createLayout()
{
    bookInfoLayout = new QGridLayout;
    issueLayout = new QVBoxLayout;
    tableLayout = new QHBoxLayout;

    mainLayout = new QVBoxLayout;
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

    tableLayout->addWidget(studentsTable);
    tableLayout->addLayout(issueLayout);

    mainLayout->addLayout(bookInfoLayout);
    mainLayout->addLayout(tableLayout);

    this->setLayout(mainLayout);
}

void IssueBookPage::searchStudent(QString s)
{
    model->setFilter("rollNo LIKE '%"+s+"%'");
    qDebug() << "rollNo LIKE '%"+s+"%'";
}
