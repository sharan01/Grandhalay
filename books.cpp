#include "books.h"

Books::Books(QWidget *parent) :
    QWidget(parent)
{
    qDebug() << "books constructed";
    model = new QSqlRelationalTableModel;
    proxyModel = new QSortFilterProxyModel;

    model->setTable("books");
    model->select();
    proxyModel->setSourceModel(model);

    //actions
    addCopyAction = new QAction("Add Copies",this);
    removeCopyAction = new QAction("Remove Copy",this);
    editBookAction = new QAction("Edit", this);
    deleteBookAction = new QAction("Delete",this);
    issueBookAction = new QAction("Issue Book", this);
    viewSummaryAction = new QAction("summary", this);


    createWidgets();
    createLayout();
    createConnections();

}
void Books::createWidgets()
{
    branchSelector = new QComboBox;
    addBookButton = new QPushButton("Add Book");
    searchBar = new QLineEdit;
    searchRadioTitle = new QRadioButton;
    searchRadioAuthor = new QRadioButton;
    searchButton = new QPushButton("search");
    booksTable = new QTableView;

    abw = new AddBookWizard(this);
    //abw = std::make_shared(new AddBookWizard);


    isbk = new IssueBook;
    //ibw = new IssueBookWizard(this);
    completer = new QCompleter(model);


    //set
    branchSelector->addItem("ALL");
    branchSelector->addItem("CIVIL");
    branchSelector->addItem("CSE");
    branchSelector->addItem("ECE");
    branchSelector->addItem("EEE");
    branchSelector->addItem("IT");
    branchSelector->addItem("COMMON");
    searchRadioAuthor->setText("Author");
    searchRadioTitle->setText("Title");
    booksTable->setModel(model);
    booksTable->setSortingEnabled(true);
    booksTable->setColumnHidden(0,true);
    booksTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    booksTable->setContextMenuPolicy(Qt::ActionsContextMenu);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setCompletionColumn(1);
    searchBar->setCompleter(completer);
    searchRadioTitle->setChecked(true);

    //actions
    booksTable->addAction(addCopyAction);
    booksTable->addAction(this->editBookAction);
    booksTable->addAction(this->deleteBookAction);
    booksTable->addAction(this->issueBookAction);
    booksTable->addAction(this->viewSummaryAction);

    booksTable->addAction(new QAction("remove Copy",this));
}

void Books::createLayout()
{
    searchLayout = new QGridLayout;
    bookTopLayout = new QHBoxLayout;
    bookLayout = new QVBoxLayout;

    //
    searchLayout->addWidget(searchBar,0,0,1,3);
    searchLayout->addWidget(searchRadioTitle,1,0,1,1);
    searchLayout->addWidget(searchRadioAuthor,1,1,1,1);
    searchLayout->addWidget(searchButton,1,2,1,1);

    bookTopLayout->addWidget(branchSelector);
    bookTopLayout->addWidget(addBookButton);
    bookTopLayout->addWidget(new QWidget,100);
    bookTopLayout->addLayout(searchLayout);

    bookTopLayout->addStretch(5);
    bookTopLayout->setAlignment(searchLayout,Qt::AlignCenter);
    bookLayout->addLayout(bookTopLayout);
    bookLayout->addWidget(booksTable);
    this->setLayout(bookLayout);
    //this->setMaximumSize(600,400);
}

void Books::createConnections()
{
    QObject::connect(addBookButton,SIGNAL(clicked()),this,SLOT(addBook()));
    //QObject::connect(abw,SIGNAL(accepted()),model,SLOT(select()));

    QObject::connect(branchSelector,SIGNAL(activated(QString)),this,SLOT(filterBooks(QString)));
    QObject::connect(searchRadioTitle,SIGNAL(toggled(bool)),this,SLOT(searchCompleter()));
    QObject::connect(searchRadioAuthor,SIGNAL(toggled(bool)),this,SLOT(searchCompleter()));
    QObject::connect(searchBar,SIGNAL(returnPressed()),this,SLOT(searchBooks()));
    QObject::connect(searchButton,SIGNAL(clicked()),this,SLOT(searchBooks()));

    //actions
    QObject::connect(addCopyAction,SIGNAL(triggered()),this,SLOT(addCopy()));
    QObject::connect(editBookAction,SIGNAL(triggered()),this,SLOT(editBook()));
    QObject::connect(deleteBookAction,SIGNAL(triggered()),this,SLOT(deleteBook()));
    QObject::connect(issueBookAction,SIGNAL(triggered()),this,SLOT(issueBook()));
    QObject::connect(viewSummaryAction,SIGNAL(triggered()),this,SLOT(viewSummary()));



}

void Books::filterBooks(QString s)
{
    if(s=="ALL"){
        model->setFilter("");
    }else{
        model->setFilter("branch='"+s+"'");
    }

}
void Books::searchBooks()
{
    QString s = searchBar->text();
    if(searchRadioTitle->isChecked()){
        model->setFilter("title LIKE '%"+s+"%'");
    }
    if(searchRadioAuthor->isChecked()){
        model->setFilter("author LIKE '%"+s+"%'");
    }
}
void Books::searchCompleter()
{
    if(searchRadioTitle->isChecked()){
        completer->setCompletionColumn(1);
    }
    if(searchRadioAuthor->isChecked()){
        completer->setCompletionColumn(2);
    }
}

void Books::addBook()
{
    std::unique_ptr<AddBookWizard> aabw(abw);
    abw = new AddBookWizard(this);
    abw->show();

    model->select();


}
void Books::addCopy()
{
    qDebug() << "addcopy clicked";
    QItemSelectionModel *select = booksTable->selectionModel();
    QModelIndex i = select->currentIndex();
    QSqlRecord record = model->record(i.row());
    QString bid = record.field("bookID").value().toString();
    QString isbn = record.field("ISBN").value().toString();

    AddCopyWizard *aacw = acw;

    acw = new AddCopyWizard(bid,isbn,this);

    delete aacw;

    acw->show();
}

void Books::editBook()
{
    std::vector<QString> s;

    QItemSelectionModel *select = booksTable->selectionModel();
    QModelIndex i = select->currentIndex();
    QSqlRecord record = model->record(i.row());

    s.push_back(record.field("bookID").value().toString());
    s.push_back(record.field("ISBN").value().toString());
    s.push_back(record.field("Title").value().toString());
    s.push_back(record.field("Author").value().toString());
    s.push_back(record.field("Publisher").value().toString());
    s.push_back(record.field("PublishedDate").value().toString());
    s.push_back(record.field("Branch").value().toString());


    EditBookWizard *eebw = ebw;
    ebw = new EditBookWizard(s,this);
    ebw->show();

    delete eebw;


    model->select();
}

void Books::deleteBook()
{

    QItemSelectionModel *select = booksTable->selectionModel();
    QModelIndex i = select->currentIndex();
    model->removeRow(i.row());

}

void  Books::issueBook()
{
    QItemSelectionModel *select = booksTable->selectionModel();
    QModelIndex i = select->currentIndex();
    QSqlRecord record = model->record(i.row());
    QString bookID = record.field("bookID").value().toString();


    qDebug() << bookID;
    IssueBookWizard *iibw = ibw;

    ibw = new IssueBookWizard(bookID,this);
    delete iibw;


    ibw->show();


}
void Books::confirmIssueBook()
{
    if(isbk->studentsTable->currentIndex().isValid()){
        QItemSelectionModel *select = isbk->studentsTable->selectionModel();
        QModelIndex i = select->currentIndex();
        QSqlRecord record = isbk->model->record(i.row());

        QString sid = record.field("studentID").value().toString();
        QString bid = QString::number(isbk->bookID);
        QDate d = isbk->returnDateI->date();
        QString q = QString("INSERT INTO issue(bookID,studentId,returnDate) values(%1, %2,'%3-%4-%5')").arg(bid,sid).arg(d.year()).arg(d.month()).arg(d.day());
        QSqlQuery qr(q);

            if(qr.exec()){
                qDebug() << "query done";
            }
            qDebug() << "selection valid";



        //qDebug() << record.field("studentID").value().toInt() << q << sid << d.day() << d.month() << d.year();




        isbk->close();

    }
}

void Books::viewSummary()
{
    QItemSelectionModel *select = booksTable->selectionModel();
    QModelIndex i = select->currentIndex();
    QSqlRecord record = model->record(i.row());
    QString bookID = record.field("bookID").value().toString();
    qDebug() << "bookid of summary caled" << bookID;
    summaryWizard *ssw = sw;

    delete ssw;
    sw = new summaryWizard(bookID,this);

    sw->show();

}

