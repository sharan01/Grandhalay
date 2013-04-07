#include "issuebookwizard.h"

IssueBookWizard::IssueBookWizard(QWidget *parent) :
    QWizard(parent)
{
    addPage(new SelectBookNumber);
    addPage(new IssueBookPage);

    accept();
}

void IssueBookWizard::accept()
{
    QDialog::accept();
}
 // ========= select book number page =============//

SelectBookNumber::SelectBookNumber(QWidget *parent) :
    QWizardPage(parent)
{
    selectCopyLabel = new QLabel("Select from Available Copies");
    copyNumbers = new QListView;
    layout = new QVBoxLayout;

    model = new QSqlRelationalTableModel;

    layout->addWidget(selectCopyLabel);
    layout->addWidget(copyNumbers);
    setLayout(layout);

    model->setTable("bookNumbers");
    model->select();
    copyNumbers->setModel(model);
    //copyNumbers->setModelColumn(1);
}
void SelectBookNumber::setISBN(QString s)
{
    ISBN = s;
    //model->setFilter("");
}


// =============== issue book page ============= //

IssueBookPage::IssueBookPage(QWidget *parent) :
    QWizardPage(parent)
{

}
