#include "returnbookwizarad.h"

ReturnBookWizarad::ReturnBookWizarad(QWidget *parent) :
    QWizard(parent)
{
    addPage(new SelectBookPage);
}
void ReturnBookWizarad::accept()
{
    QDialog::accept();
}

// ================================= //

SelectBookPage::SelectBookPage(QWidget *parent) :
    QWizardPage(parent)
{
    rollLabel.setText("Roll Number");
    nameLabel.setText("Name");
    branchLabel.setText("Branch");
    booksTaken.setText("Books Taken");

    layout.addWidget(&rollLabel,0,0);
    layout.addWidget(&roll,0,1);
    layout.addWidget(&nameLabel,0,2);
    layout.addWidget(&name,0,3);
    layout.addWidget(&branchLabel,1,0);
    layout.addWidget(&branch,1,1);
    layout.addWidget(&booksTaken,2,0);
    layout.addWidget(&issuedBooksTable,3,0,0,4);


    setLayout(&layout);
}


void SelectBookPage::getStudentInfo()
{

}

//====================================//
ReturnFinalPage::ReturnFinalPage(QWidget *parent):
    QWizardPage(parent)
{

}
