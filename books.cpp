#include "books.h"

Books::Books()
{


    //layouts
    searchLayout = new QGridLayout;
    bookTopLayout = new QHBoxLayout;
    bookLayout = new QVBoxLayout;

    //widgets
    branchSelector = new QComboBox;
    addBookButton = new QPushButton("Add Book");
    searchBar = new QLineEdit;
    searchRadioTitle = new QRadioButton;
    searchRadioAuthor = new QRadioButton;
    searchButton = new QPushButton("search");
    booksTable = new QTableView;

    model = new QSqlRelationalTableModel;
    proxyModel = new QSortFilterProxyModel;

    //set
    branchSelector->addItem("ALL");
    branchSelector->addItem("CIVIL");
    branchSelector->addItem("CSE");
    branchSelector->addItem("ECE");
    branchSelector->addItem("EEE");
    branchSelector->addItem("IT");
    searchRadioAuthor->setText("Author");
    searchRadioTitle->setText("Title");
    model->setTable("books");
    model->select();
    proxyModel->setSourceModel(model);
    booksTable->setModel(proxyModel);
    booksTable->setSortingEnabled(true);

    adbk = new AddBook;

    completer = new QCompleter(proxyModel);

    completer->setCaseSensitivity(Qt::CaseInsensitive);

    searchBar->setCompleter(completer);

    searchRadioTitle->setChecked(true);
    completer->setCompletionColumn(1);

    addBookAction = new QAction("add book", this);
    QObject::connect(this->addBookAction,SIGNAL(triggered()),this,SLOT(context()));

    booksTable->addAction(this->addBookAction);
    booksTable->addAction(new QAction("edit",this));
    booksTable->addAction(new QAction("delete",this));
    booksTable->setContextMenuPolicy(Qt::ActionsContextMenu);

    QObject::connect(adbk->ok,SIGNAL(clicked()),this,SLOT(confirmAddBook()));

    QObject::connect(this->addBookButton,SIGNAL(clicked()),this,SLOT(addBook()));

    QObject::connect(this->branchSelector,SIGNAL(activated(QString)),this,SLOT(filterBooks(QString)));
    QObject::connect(this->searchRadioTitle,SIGNAL(toggled(bool)),this,SLOT(searchCompleter()));
    QObject::connect(this->searchRadioAuthor,SIGNAL(toggled(bool)),this,SLOT(searchCompleter()));
    QObject::connect(this->searchBar,SIGNAL(returnPressed()),this,SLOT(searchBooks()));
    QObject::connect(this->searchButton,SIGNAL(clicked()),this,SLOT(searchBooks()));


    //set layouts

    searchLayout->addWidget(searchBar,0,0,1,3);
    searchLayout->addWidget(searchRadioTitle,1,0,1,1);
    searchLayout->addWidget(searchRadioAuthor,1,1,1,1);
    searchLayout->addWidget(searchButton,1,2,1,1);

    bookTopLayout->addWidget(branchSelector);
    bookTopLayout->addWidget(addBookButton);
    bookTopLayout->addLayout(searchLayout);

    bookLayout->addLayout(bookTopLayout);
    bookLayout->addWidget(booksTable);
    this->setLayout(bookLayout);
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
void Books::context()
{

    QItemSelectionModel *select = booksTable->selectionModel();
    QModelIndex i = select->currentIndex();
    proxyModel->removeRow(i.row());
    qDebug() << i.row() << i.model();

}
void Books::addBook()
{
    foreach(QLineEdit *widget, adbk->findChildren<QLineEdit*>()) {
        widget->clear();
    }
    adbk->exec();
}
void Books::confirmAddBook()
{
    QString bni = adbk->bookNoInput->text();
    QString ti = adbk->titleInput->text();
    QString ai = adbk->authorInput->text();
    QString  ci = adbk->copiesInput->text();
    QString  pi = adbk->priceInput->text();
    QString  bi = adbk->branchInput->currentText();

    QString qr;
    qr = "INSERT INTO books(title,author,copies,branch,price) VALUES('"+ ti +"','"+ ai +"','"+ ci +"','"+ bi +"','"+ pi +"')";
    qDebug() << qr;
    QSqlQuery  q(qr);
    model->select();
    adbk->hide();

    //jjq.exec();
}
