#include "addmemberwizard.h"

AddMemberWizard::AddMemberWizard(QWidget *parent) :
    QWizard(parent)
{
    addPage(new MembersPage);
    setModal(true);
    this->setButtonText(FinishButton,"Add Student");
    this->button(BackButton)->close();
}
void AddMemberWizard::accept()
{
    QString branches[7]={"CIVIL","CSE","ECE","EEE","IT","MECH","M.Tech"};

    QString roll = field("roll").toString();
    QString name = field("name").toString();
    QString branch = branches[field("branch").toInt()];
    QString phone = field("phone").toString();
    QString email = field("email").toString();
    QString qr = QString("INSERT INTO members(roll,name,branch,phone,email) VALUES('%1','%2','%3','%4','%5')").arg(roll,name,branch,phone,email);
    QSqlQuery q(qr);

    QDialog::accept();

    this->cleanupPage(0);

}


// m================= nenebers page =========== //

MembersPage::MembersPage(QWidget *parent) :
    QWizardPage(parent)
{
    createWidgets();
    createLayout();
    registerFields();
}
void MembersPage::createWidgets()
{
    rollLabel = new QLabel("Roll Number");
    nameLabel = new QLabel("Name");
    branchLabel = new QLabel("Branch");
    phoneLabel = new QLabel("Mobile Number");
    emailLabel = new QLabel("Email Address");

    branchSelector = new QComboBox;

    rollEdit = new QLineEdit;
    nameEdit = new QLineEdit;
    phoneEdit = new QLineEdit;
    emailEdit = new QLineEdit;


    branchSelector->addItem("CIVIL");
    branchSelector->addItem("CSE");
    branchSelector->addItem("ECE");
    branchSelector->addItem("EEE");
    branchSelector->addItem("IT");
    branchSelector->addItem("MECH");
    branchSelector->addItem("M.Tech");
}
void MembersPage::createLayout()
{
    layout = new QGridLayout;

    layout->addWidget(rollLabel,0,0);
    layout->addWidget(rollEdit,0,1);
    layout->addWidget(nameLabel,1,0);
    layout->addWidget(nameEdit,1,1);
    layout->addWidget(branchLabel,2,0);
    layout->addWidget(branchSelector,2,1);
    layout->addWidget(phoneLabel,3,0);
    layout->addWidget(phoneEdit,3,1);
    layout->addWidget(emailLabel,4,0);
    layout->addWidget(emailEdit,4,1);

    setLayout(layout);
}

void MembersPage::registerFields()
{
    registerField("roll*",rollEdit);
    registerField("name*",nameEdit);
    registerField("branch",branchSelector);
    registerField("phone*",phoneEdit);
    registerField("email*",emailEdit);
}
