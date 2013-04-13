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
    editBookAction = new QAction("Edit", this);
    deleteBookAction = new QAction("Delete",this);
    issueBookAction = new QAction("Issue Book", this);
    viewSummaryAction = new QAction("summary", this);

    //widgets
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
    ibw = new IssueBookWizard(this);
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
    booksTable->addAction(this->editBookAction);
    booksTable->addAction(this->deleteBookAction);
    booksTable->addAction(this->issueBookAction);
    booksTable->addAction(this->viewSummaryAction);
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
    QObject::connect(this->addBookButton,SIGNAL(clicked()),this,SLOT(addBook()));

    QObject::connect(this->branchSelector,SIGNAL(activated(QString)),this,SLOT(filterBooks(QString)));
    QObject::connect(this->searchRadioTitle,SIGNAL(toggled(bool)),this,SLOT(searchCompleter()));
    QObject::connect(this->searchRadioAuthor,SIGNAL(toggled(bool)),this,SLOT(searchCompleter()));
    QObject::connect(this->searchBar,SIGNAL(returnPressed()),this,SLOT(searchBooks()));
    QObject::connect(this->searchButton,SIGNAL(clicked()),this,SLOT(searchBooks()));

    //actions
    QObject::connect(this->editBookAction,SIGNAL(triggered()),this,SLOT(editBook()));
    QObject::connect(this->deleteBookAction,SIGNAL(triggered()),this,SLOT(deleteBook()));
    QObject::connect(this->issueBookAction,SIGNAL(triggered()),this,SLOT(issueBook()));
    QObject::connect(this->viewSummaryAction,SIGNAL(triggered()),this,SLOT(viewSummary()));

    QObject::connect(isbk->issueButton,SIGNAL(clicked()),SLOT(confirmIssueBook()));
    QObject::connect(isbk->studentsTable,SIGNAL(clicked(QModelIndex)),this,SLOT(enablebut()));

    QObject::connect(abw,SIGNAL(accepted()),model,SLOT(select()));
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

void Books::editBook()
{/*
    QItemSelectionModel *select = booksTable->selectionModel();
    QModelIndex i = select->currentIndex();
    QSqlRecord record = model->record(i.row());
    QVariant ss = record.field("title").value().toString();
    qDebug() << ss;
    edbk->currentID = record.field("id").value().toInt();
    edbk->bookNoInput->setText(record.field("number").value().toString());
    edbk->titleInput->setText(record.field("title").value().toString());
    edbk->authorInput->setText(record.field("author").value().toString());
    edbk->copiesInput->setText(record.field("copies").value().toString());
    edbk->priceInput->setText(record.field("price").value().toString());
    edbk->branchInput->setCurrentIndex(edbk->branchInput->findText(record.field("branch").value().toString()));

    edbk->exec();
    */
}

void Books::confirmEditBook()
{/*
    QString bni = edbk->bookNoInput->text();
    QString ti = edbk->titleInput->text();
    QString ai = edbk->authorInput->text();
    QString  ci = edbk->copiesInput->text();
    QString  pi = edbk->priceInput->text();
    QString  bi = edbk->branchInput->currentText();
    QString qr = QString("UPDATE books SET title='%1',author='%2',copies='%3',branch='%4',price='%5',number='%6' WHERE id=%7").arg(ti,ai,ci,bi,pi,bni,QString::number(edbk->currentID));

    qDebug() << qr;
    QSqlQuery  q(qr);
    model->select();
    edbk->close();


    foreach(QLineEdit *widget, edbk->findChildren<QLineEdit*>()) {
        widget->clear();
    }*/
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
    QString isbn = record.field("ISBN").value().toString();

    ibw->sbn->setISBN(isbn);
    qDebug() << isbn;

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

}
void Books::enablebut()
{
    isbk->issueButton->setEnabled(true);
}
