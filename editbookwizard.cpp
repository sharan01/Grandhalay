#include "editbookwizard.h"

EditBookWizard::EditBookWizard(std::vector<QString> s,QWidget *parent) :
    QWizard(parent)
{
    addPage(new EditPage(s));
}

//===================================================///

EditPage::EditPage(QWidget *parent = 0) :
    QWizardPage(parent)
{

}


EditPage::EditPage(std::vector<QString> s,QWidget *parent = 0) :
    QWizardPage(parent)
{
    s.resize(5);
    // create widgets ===============================
    isbnLabel.setText("ISBN");
    titleLabel.setText("Title");
    authorLabel.setText("Author");
    publisherLabel.setText("Publisher");
    publishedDateLabel.setText("Published Date");

    isbnEdit.setText(s[0]);
    titleEdit.setText(s[1]);
    authorEdit.setText(s[2]);
    publisherEdit.setText(s[3]);
    publishedDateEdit.setText(s[4]);


    // create layout ==================================
    layout.addRow("ISBN",&isbnEdit);
    layout.addRow("Title",&titleEdit);
    layout.addRow("Author",&authorEdit);
    layout.addRow("Publisher",&publisherEdit);
    layout.addRow("Publisher Date",&publishedDateEdit);

    setLayout(&layout);






















}
