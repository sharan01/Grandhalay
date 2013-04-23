#include "summarywizard.h"



summaryWizard::summaryWizard(QString bID, QWidget *parent) :
    QWizard(parent), swp(bID,this)
{
    addPage(&swp);
}













summaryWizardPage::summaryWizardPage(QString bid, QWidget *parent) :
    QWizardPage(parent), bookID(bid)
{
    totalCopiesLabel.setText("No of Copies");
    availbleCopiesLabel.setText("Available Copies");
    booksIssuedLabel.setText("Issued to ");
    totalCopiesEdit.setDisabled(true);
    availbleCopiesEdit.setDisabled(true);

    issuedTable.setModel(&model);
    model.setTable("issue");
    model.select();


    // layout
    layout.addWidget(&totalCopiesLabel,0,0);
    layout.addWidget(&totalCopiesEdit,0,1);
    layout.addWidget(&availbleCopiesLabel,0,2);
    layout.addWidget(&availbleCopiesEdit,0,3);
    layout.addWidget(&booksIssuedLabel,1,0);
    layout.addWidget(&issuedTable,2,0,1,4);
    setLayout(&layout);



    // initlize

    model.setFilter("bookID=" + bookID);





}
