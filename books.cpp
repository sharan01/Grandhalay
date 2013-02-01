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
    branchSelector->addItem("common");
    searchRadioAuthor->setText("Author");
    searchRadioTitle->setText("Title");
    model->setTable("books");
    model->select();
    proxyModel->setSourceModel(model);
    booksTable->setModel(model);
    booksTable->setSortingEnabled(true);

    adbk = new AddBook(1);
    edbk = new AddBook(2);

    completer = new QCompleter(model);

    completer->setCaseSensitivity(Qt::CaseInsensitive);

    searchBar->setCompleter(completer);

    searchRadioTitle->setChecked(true);
    completer->setCompletionColumn(1);

    editBookAction = new QAction("Edit", this);
    deleteBookAction = new QAction("Delete",this);


    booksTable->addAction(this->editBookAction);
    booksTable->addAction(this->deleteBookAction);
    booksTable->addAction(new QAction("issue",this));
    booksTable->setContextMenuPolicy(Qt::ActionsContextMenu);



    QObject::connect(this->addBookButton,SIGNAL(clicked()),this,SLOT(addBook()));

    QObject::connect(this->branchSelector,SIGNAL(activated(QString)),this,SLOT(filterBooks(QString)));
    QObject::connect(this->searchRadioTitle,SIGNAL(toggled(bool)),this,SLOT(searchCompleter()));
    QObject::connect(this->searchRadioAuthor,SIGNAL(toggled(bool)),this,SLOT(searchCompleter()));
    QObject::connect(this->searchBar,SIGNAL(returnPressed()),this,SLOT(searchBooks()));
    QObject::connect(this->searchButton,SIGNAL(clicked()),this,SLOT(searchBooks()));

    //actions
    QObject::connect(this->editBookAction,SIGNAL(triggered()),this,SLOT(editBook()));
    QObject::connect(this->deleteBookAction,SIGNAL(triggered()),this,SLOT(deleteBook()));

    QObject::connect(adbk->ok,SIGNAL(clicked()),this,SLOT(confirmAddBook()));
    QObject::connect(edbk->edit,SIGNAL(clicked()),this,SLOT(confirmEditBook()));

    //set layouts

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


    QString qr = QString("INSERT INTO books(title,author,copies,branch,price,number) VALUES('%1','%2','%3','%4','%5','%6')").arg(ti,ai,ci,bi,pi,bni);
    qDebug() << qr;
    QSqlQuery  q(qr);
    model->select();


    foreach(QLineEdit *widget, adbk->findChildren<QLineEdit*>()) {
        widget->clear();
    }
    adbk->close();


}
void Books::editBook()
{
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
}

void Books::confirmEditBook()
{
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
    }
}

void Books::deleteBook()
{

    QItemSelectionModel *select = booksTable->selectionModel();
    QModelIndex i = select->currentIndex();
    model->removeRow(i.row());

}
