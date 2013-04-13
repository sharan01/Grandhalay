#include "addbook.h"

AddBook::AddBook(QWidget *parent) :
    QDialog(parent)
{
    qDebug() << "add book constructed";
    info = new QLabel("Please enter book details below");
    bookNo = new QLabel("Book Number");
    title = new QLabel("Title");
    author = new QLabel("Author");
    copies = new QLabel("Number of Copies");
    branch = new QLabel("Branch");
    price = new QLabel("Price");

    bookNoInput = new QLineEdit;
    titleInput = new QLineEdit;
    authorInput = new QLineEdit;
    copiesInput = new QLineEdit;
    priceInput = new QLineEdit;

    branchInput = new QComboBox;

    ok = new QPushButton("OK");
    edit = new QPushButton("Edit");
    cancel = new QPushButton("CANCEL");
    mainlayout = new QVBoxLayout;
    formLayout = new QFormLayout;
    buttonLayout = new QHBoxLayout;

    //set
    branchInput->addItem("CIVIL");
    branchInput->addItem("CSE");
    branchInput->addItem("ECE");
    branchInput->addItem("EEE");
    branchInput->addItem("IT");
    branchInput->addItem("MECH");
    branchInput->addItem("common");

    //layouts
    formLayout->addRow(bookNo,bookNoInput);
    formLayout->addRow(title,titleInput);
    formLayout->addRow(author,authorInput);
    formLayout->addRow(copies,copiesInput);
    formLayout->addRow(branch,branchInput);
    formLayout->addRow(price,priceInput);


    buttonLayout->addWidget(cancel);

    buttonLayout->addWidget(ok);

    mainlayout->addWidget(info);
    mainlayout->addLayout(formLayout);
    mainlayout->addLayout(buttonLayout);

    this->setLayout(mainlayout);


}
