#include "members.h"

Members::Members(QWidget *parent) :
    QWidget(parent)
{
    createModels();

    createWidgets();
    createActions();
    createLayout();
    createConnections();
}

void Members::createModels()
{
    model = new QSqlRelationalTableModel(this);
    proxyModel = new QSortFilterProxyModel(this);

    model->setTable("members");
    model->select();
    proxyModel->setSourceModel(model);
}
void Members::createActions()
{
    editMemberAction = new QAction("Edit",this);
    deleteMemberAction = new QAction("Delete Student", this);
    returBookAction = new QAction("return Book", this);
    viewSummaryAction = new QAction("view Summary",this);

    membersTable->addAction(editMemberAction);
    membersTable->addAction(returBookAction);
    membersTable->addAction(viewSummaryAction);
    membersTable->addAction(deleteMemberAction);

}

void Members::createWidgets()
{
    branchSelector = new QComboBox;
    addMemberButton = new QPushButton("Add Sudent");
    searchBar = new QLineEdit;
    searchRadioRoll = new QRadioButton("Roll Number");
    searchRadioName = new QRadioButton("Name");
    searchButton = new QPushButton("search");
    membersTable = new QTableView;

    amw = new AddMemberWizard(this);

    membersTable->setModel(model);
    branchSelector->addItem("ALL");
    branchSelector->addItem("CIVIL");
    branchSelector->addItem("CSE");
    branchSelector->addItem("ECE");
    branchSelector->addItem("EEE");
    branchSelector->addItem("IT");
    branchSelector->addItem("MECH");
    branchSelector->addItem("M.Tech");
    branchSelector->addItem("Faculty");

    searchRadioName->setChecked(true);
    membersTable->setSelectionBehavior(QAbstractItemView::SelectRows);

}
void Members::createLayout()
{
    searchLayout = new QGridLayout;
    memberTopLayout = new QHBoxLayout;
    memberLayout = new QVBoxLayout;

    searchLayout->addWidget(searchBar,0,0,1,3);
    searchLayout->addWidget(searchRadioRoll,1,0,1,1);
    searchLayout->addWidget(searchRadioName,1,1,1,1);
    searchLayout->addWidget(searchButton,1,2,1,1);

    memberTopLayout->addWidget(branchSelector);
    memberTopLayout->addWidget(addMemberButton);
    memberTopLayout->addWidget(new QWidget,100);
    memberTopLayout->addLayout(searchLayout);

    memberLayout->addLayout(memberTopLayout);
    memberLayout->addWidget(membersTable);

    this->setLayout(memberLayout);
}
void Members::createConnections()
{
    QObject::connect(branchSelector,SIGNAL(activated(QString)),this,SLOT(filterMembers(QString)));
    QObject::connect(addMemberButton,SIGNAL(clicked()),this,SLOT(addMember()));

    QObject::connect(this->searchBar,SIGNAL(returnPressed()),this,SLOT(searchMembers()));
    QObject::connect(this->searchButton,SIGNAL(clicked()),this,SLOT(searchMembers()));

    QObject::connect(amw,SIGNAL(accepted()),this->model,SLOT(select()));

    //qactions
    QObject::connect(returBookAction,SIGNAL(triggered()),this,SLOT(returnBook()));
    QObject::connect(viewSummaryAction,SIGNAL(triggered()),this,SLOT(viewSummary()));
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

void Members::searchMembers()
{
    QString s = searchBar->text();
    if(searchRadioRoll->isChecked()){
        model->setFilter("roll LIKE '%"+s+"%'");
    }
    if(searchRadioName->isChecked()){
        model->setFilter("name LIKE '%"+s+"%'");
    }
}
void Members::addMember()
{
    amw->show();
    model->select();
}
void Members::returnBook()
{
    ReturnBookWizarad *rrbw = rbw;

    rbw = new ReturnBookWizarad(this);
    delete rrbw;

    rbw->show();
}
void Members::viewSummary()
{

}
