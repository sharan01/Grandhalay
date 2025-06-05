#include <QSqlRecord>
#include "returnbookwizarad.h"

ReturnBookWizarad::ReturnBookWizarad(QWidget *parent) :
    QWizard(parent)
{
    addPage(&sbp);
    addPage(&rfp);
    setButtonText(QWizard::FinishButton, "Return Book");
}

void ReturnBookWizarad::setMemberRoll(const QString &roll)
{
    m_memberRoll = roll;
    sbp.setMember(roll);
}

void ReturnBookWizarad::accept()
{
    QString bookNo = field("bookNo").toString();
    QSqlQuery q;
    q.exec(QString("SELECT memberID FROM members WHERE roll='%1'").arg(m_memberRoll));
    if(q.next()) {
        QString memberID = q.value(0).toString();
        QSqlQuery del(QString("DELETE FROM issue WHERE memberID=%1 AND bookNo=%2").arg(memberID).arg(bookNo));
        QSqlQuery upd(QString("UPDATE bookNumbers SET issued=0 WHERE bookNo=%1").arg(bookNo));
    }
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

    roll.setReadOnly(true);
    name.setReadOnly(true);
    branch.setReadOnly(true);
    selectedBookEdit.setVisible(false);

    layout.addWidget(&rollLabel,0,0);
    layout.addWidget(&roll,0,1);
    layout.addWidget(&nameLabel,0,2);
    layout.addWidget(&name,0,3);
    layout.addWidget(&branchLabel,1,0);
    layout.addWidget(&branch,1,1);
    layout.addWidget(&booksTaken,2,0);
    layout.addWidget(&issuedBooksTable,3,0,1,4);

    setLayout(&layout);

    registerField("bookNo", &selectedBookEdit);
    connect(&issuedBooksTable, &QTableView::clicked, this, &SelectBookPage::rowSelected);
}

void SelectBookPage::setMember(const QString &rollNo)
{
    roll.setText(rollNo);
    QSqlQuery q;
    q.prepare("SELECT memberID, Name, Branch FROM members WHERE roll=?");
    q.addBindValue(rollNo);
    if(q.exec() && q.next()) {
        memberID = q.value(0).toString();
        name.setText(q.value(1).toString());
        branch.setText(q.value(2).toString());
        model.setTable("issue");
        model.setFilter(QString("memberID='%1'").arg(memberID));
        model.select();
        issuedBooksTable.setModel(&model);
        issuedBooksTable.hideColumn(0);
        issuedBooksTable.hideColumn(3);
    }
}

void SelectBookPage::rowSelected(const QModelIndex &index)
{
    QSqlRecord r = model.record(index.row());
    selectedBookEdit.setText(r.value("bookNo").toString());
}

int SelectBookPage::nextId() const
{
    return 1;
}

//====================================//
ReturnFinalPage::ReturnFinalPage(QWidget *parent):
    QWizardPage(parent)
{
    setTitle("Return Book");
    infoLabel.setText("Press Finish to return the selected book.");
    layout.addWidget(&infoLabel);
    setLayout(&layout);
}
