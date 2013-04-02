#include "members.h"

Members::Members(QWidget *parent) :
    QWidget(parent)
{
    createModels();
    createWidgets();
    createLayout();
    createConnections();
}

void Members::createModels()
{
    model = new QSqlRelationalTableModel;
    proxyModel = new QSortFilterProxyModel;

    model->setTable("students");
    model->select();
    proxyModel->setSourceModel(model);
}

void Members::createWidgets()
{
    branchSelector = new QComboBox;
    addMemberButton = new QPushButton("Add Sudent");
    searchBar = new QLineEdit;
    membersTable = new QTableView;

    membersTable->setModel(model);
    branchSelector->addItem("ALL");
    branchSelector->addItem("CIVIL");
    branchSelector->addItem("CSE");
    branchSelector->addItem("ECE");
    branchSelector->addItem("EEE");
    branchSelector->addItem("IT");
    branchSelector->addItem("MECH");
    branchSelector->addItem("M.Tech");

    searchBar->setPlaceholderText("Roll Numbers");
}
void Members::createLayout()
{
    memberTopLayout = new QHBoxLayout;
    memberLayout = new QVBoxLayout;

    memberTopLayout->addWidget(branchSelector);
    memberTopLayout->addWidget(addMemberButton);
    memberTopLayout->addWidget(searchBar);

    memberLayout->addLayout(memberTopLayout);
    memberLayout->addWidget(membersTable);

    this->setLayout(memberLayout);
}
void Members::createConnections()
{
    QObject::connect(branchSelector,SIGNAL(activated(QString)),this,SLOT(filterMembers(QString)));
    QObject::connect(searchBar,SIGNAL(textChanged(QString)),this,SLOT(searchMembers(QString)));
}



// slots =============

void Members::filterMembers(QString s)
{
    if(s=="ALL"){
        model->setFilter("");
    }else{
        model->setFilter("branch='" +s+ "'");
    }
}

void Members::searchMembers(QString s)
{
    model->setFilter("rollNo LIKE'%"+s+"%'");
}
