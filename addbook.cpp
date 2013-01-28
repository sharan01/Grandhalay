#include "addbook.h"

AddBook::AddBook()
{
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

    //layouts
    formLayout->addRow(bookNo,bookNoInput);
    formLayout->addRow(title,titleInput);
    formLayout->addRow(author,authorInput);
    formLayout->addRow(copies,copiesInput);
    formLayout->addRow(branch,branchInput);
    formLayout->addRow(price,priceInput);

    buttonLayout->addWidget(ok);
    buttonLayout->addWidget(cancel);

    mainlayout->addWidget(info);
    mainlayout->addLayout(formLayout);
    mainlayout->addLayout(buttonLayout);

    this->setLayout(mainlayout);


}
